/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/08 20:54:28 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//expand variables
char	*expand(t_shell *shell, char *str)
{
	char	*value;

	value = get_env_value(shell, str);
	return (value);
}

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

//counts len depending on the type of variable
/* int	convert_len(char *str, int i, t_quote q)
{
	int	len;

	(void)q;
	if((str[i] == '\'' || str[i] == '\"') && q.q_closed)
		return (1);
	if (ft_isalnum(str[i]) || str[i] == '$')
		len = strlen_b_sc(str + i);
	else
		len = strlen_before_a(str + i);
	return (len);
} */

//converts a string with variables to a string with values
//eg. "echo $USER" -> "echo jkoupy"
//eg. "echo $?" -> "echo 0"

//counts the length of a substring starting at i
int substr_len(char *str, int i)
{
	int len;
	char q;

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
char *expand_token(t_shell *shell, char *str)
{
	char	*substr;
	char	*expanded;
	char 	*res;
	char 	*tmp;
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
char *expand_substr(t_shell *shell, char *substr)
{
	char dom_q;
	char *res;
	
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
char *expand_vars(t_shell *shell, char *substr)
{
	char *var;
	char *value;
	int i;
	int len;
	char *res;
	char *tmp;

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
				value = expand(shell, var + 1);
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
char *copy_until_dollar(char *res, char *substr, int *i)
{
	int len;
	char *tmp;
	char *tmp2;
	
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


	/* char *tmp;
	char *tmp2;

	tmp = *res;
	while (substr[*i] && substr[*i] != '$')
	{
		tmp2 = ft_substr(substr, *i, 1);
		tmp = ft_strjoin(tmp, tmp2);
		free(tmp2);
		(*i)++;
	}
	free(*res);
	*res = tmp;
	return (*res); */

//adds a character to a string and returns the new string
/* char *add_char(char *str, char c)
{
	char *res;
	int len;
	int i;

	if (!str || !str[0])
	{
		res = malloc(sizeof(char) * 2);
		if (!res)
			return (NULL);
		res[0] = c;
		res[1] = '\0';
		if (str)
			free(str);
		return (res);
	}
	i = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(str);
	return (res);
} */


/* char	*convert_str(t_shell *shell, char *str)
{
	char	*substr;
	char	*new_str;
	int		len;
	int		i;
	t_quote	q;

	i = 0;
	q.q_closed = true;
	new_str = NULL;
	q.type = '\0';
	while (str && str[i])
	{
		len = convert_len(str, i, q);
		//printf("len: %d\n", len);
		substr = ft_substr(str, i, len);
		if(q.q_closed && is_quote(str[i]))
		{
			q.type = str[i];
			q.q_closed = false;
		}
		//printf("Str[%d]: %c\n", i, str[i]);
		printf("substr: %s\n", substr);
		if (ft_strncmp(substr, "$?", 2) == 0 && q.type != '\'')
			substr = ft_strdup(ft_itoa(shell->exitcode));
		printf("Q type: %c\n", q.type);
		if (is_var(shell, substr) && q.type != '\'')
			substr = expand(shell, substr + 1);
		else if (is_fake_var(shell, substr) && q.type != '\'')
			substr = ft_strdup("");
		new_str = ft_strjoin(new_str, substr);
		free(substr);
		printf("Q_closed: %d\n", q.q_closed);
		if(str[i] == q.type && !q.q_closed)
			q.q_closed = true;
		i += len;
	}
	return (new_str);
} */

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
