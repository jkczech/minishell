/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 11:57:41 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//expand variables in the tokens
//loop through tokens and expand them with expand_token function
void	expander(t_shell *shell)
{
	t_token	*token;
	char	*tmp;
	char	*var;

	token = shell->tokens;
	while (token)
	{
		if (!token->content || token->token == HEREDOC)
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

//separate token string into substrings by quotes
//expand substrings separately with expand_substr function
//returns the expanded string
char	*expand_token(t_shell *shell, char *str)
{
	char	*q_substr;
	char	*expanded;
	char	*res;
	int		len;
	int		i;

	i = 0;
	res = NULL;
	while (str[i])
	{
		len = q_substr_len(str, i);
		q_substr = ft_substr(str, i, len);
		expanded = expand_q_substr(shell, q_substr, \
		(int)ft_strlen(str + i) == len);
		if (!expanded || !q_substr)
			return (NULL);
		if (expanded[0] == '\'' || expanded[0] == '\"')
			remove_first_and_last_char(&expanded);
		free(q_substr);
		res = ft_strjoin_free(res, expanded);
		i += len;
	}
	return (res);
}

//counts the length of a substring starting at i
int	q_substr_len(char *str, int i)
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

//expands a substring and depending on the dominant quote type
//returns the expanded substring
//free the original substring
char	*expand_q_substr(t_shell *shell, char *substr, bool last)
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
	res = expand_vars(shell, substr, last);
	return (res);
}

void	remove_first_and_last_char(char **str)
{
	char	*new_str;
	int		i;
	int		len;

	len = ft_strlen(*str);
	new_str = (char *)malloc(sizeof(char) * len - 1);
	if (!new_str)
		return ;
	i = 1;
	while (i < len - 1)
	{
		new_str[i - 1] = (*str)[i];
		i++;
	}
	new_str[i - 1] = '\0';
	free(*str);
	*str = new_str;
}

//check if $ is followed by a valid variable
//go through tokens and expand variables
//if variable is not found, leave it as is
//if variable is found, replace it with its value
