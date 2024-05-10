/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/09 16:40:14 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* //expand variables
char	*expand(t_shell *shell, char *str)
{
	char	*value;

	value = get_env_value(shell, str);
	return (value);
} */

//gets the value of a variable in the environment
char	*get_env_value(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;
	char	*value;

	node = shell->env_list;
	while (node)
	{
		var = ((t_env *)node->content)->var;
		if (ft_strncmp(var, str, ft_strlen(var)) == 0)
		{
			value = ft_strdup(((t_env *)node->content)->value);
			if (!value)
				return (NULL);
			return (value);
		}
		node = node->next;
	}
	return (NULL);
}

//counts the length of a substring starting at i
int	substr_len(char *str, int i)
{
	int		len;
	char	q;

	len = 0;
	if (is_quote(str[i]))
	{
		q = str[i++];
		len++;
	}
	else
		q = '\0';
	while ((q && str[i] && str[i] != q) || \
			(!q && str[i] && !is_quote(str[i])))
	{
		len++;
		i++;
	}
	if (str[i] == q && q != '\0')
		len++;
	return (len);
}

//takes token string, separates into substrings and expands them separately
//returns the expanded string
char	*expand_token(t_shell *shell, char *str)
{
	char	*substr;
	char	*expanded;
	char	*res;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	res = NULL;
	while (str[i])
	{
		len = substr_len(str, i);
		substr = ft_substr(str, i, len);
		expanded = expand_substr(shell, substr);
		if (!expanded || !substr)
			return (NULL);
		tmp = ft_strdup(res);
		free(res);
		free(substr);
		res = ft_strjoin(tmp, expanded);
		free(tmp);
		free(expanded);
		i += len;
	}
	return (res);
}

//expands a substring and depending on the dominant quote type
//returns the expanded substring
//free the original substring
char	*expand_substr(t_shell *shell, char *substr)
{
	char	dom_q;
	char	*res;

	if (!substr)
		return (NULL);
	if (substr[0] == '\'' || substr[0] == '\"')
		dom_q = substr[0];
	else
		dom_q = '\0';
	if (dom_q == '\'')
		return (ft_strdup(substr));
	res = expand_vars(shell, substr);
	return (res);
}

//expand variables in a substring
//finds all variables starting with $ and expands them if they exist
//adds all the skipped characters to the new string
char	*expand_vars(t_shell *shell, char *substr)
{
	char	*var;
	char	*value;
	int		i;
	int		len;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	while (substr && substr[i])
	{
		res = copy_until_dollar(res, substr, &i);
		if (substr[i] == '$')
		{
			if (substr[i + 1] == '?')
			{
				value = ft_strdup(ft_itoa(shell->exitcode));
				tmp = ft_strdup(res);
				free(res);
				res = ft_strjoin(tmp, value);
				free(value);
				free(tmp);
				i += 2;
				continue ;
			}
			len = var_len(substr + i);
			var = ft_substr(substr, i, len);
			if (!is_possible_var(var))
			{
				tmp = ft_strdup(res);
				free(res);
				res = ft_strjoin(tmp, var);
				free(tmp);
			}
			else if (is_var(shell, var))
			{
				value = get_env_value(shell, var + 1);
				tmp = ft_strdup(res);
				free(res);
				res = ft_strjoin(tmp, value);
				free(value);
				free(tmp);
			}
			else
			{
				tmp = ft_strdup(res);
				free(res);
				res = ft_strjoin(tmp, NULL);
				free(tmp);
			}
			free(var);
			i += len;
		}
	}
	return (res);
}

//copy skipped characters to the new string until a dollar sign is found
char	*copy_until_dollar(char *res, char *substr, int *i)
{
	int		len;
	char	*tmp;
	char	*tmp2;

	len = len_until_dollar(substr, *i);
	tmp = ft_substr(substr, *i, len);
	tmp2 = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp2, tmp);
	if (!res)
		return (NULL);
	free(tmp2);
	free(tmp);
	*i += len;
	return (res);
}

//expands variables in the tokens
void	expander(t_shell *shell)
{
	t_token	*token;
	char	*tmp;
	char	*var;

	token = shell->tokens;
	while (token)
	{
		if (!token->content)
		{
			token = token->next;
			continue ;
		}
		tmp = token->content;
		var = expand_token(shell, tmp);
		if (!var)
			var = ft_strdup(tmp);
		free(tmp);
		token->content = ft_strdup(var);
		free(var);
		token = token->next;
	}
}

//check if $ is followed by a valid variable
//go through tokens and expand variables
//if variable is not found, leave it as is
//if variable is found, replace it with its value
