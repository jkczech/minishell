/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/24 14:57:45 by jakob            ###   ########.fr       */
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
int	convert_len(char *str, int i)
{
	int	len;

	if (ft_isalnum(str[i]) || str[i] == '$')
		len = strlen_b_sc(str + i);
	else
		len = strlen_before_a(str + i);
	return (len);
}

//converts a string with variables to a string with values
//eg. "echo $USER" -> "echo jkoupy"
//eg. "echo $?" -> "echo 0"
char	*convert_str(t_shell *shell, char *str)
{
	char	*substr;
	char	*new_str;
	int		len;
	int		i;
	t_quote	q;

	i = 0;
	q.q_closed = true;
	new_str = NULL;
	while (str && str[i])
	{
		if(is_quote(str[i]))
		{
			q.type = str[i];
			q.q_closed = false;
		}
		len = convert_len(str, i);
		substr = ft_substr(str, i, len);
		if (ft_strncmp(substr, "$?", 2) == 0)
			substr = ft_strdup(ft_itoa(shell->exitcode));
		if (is_var(shell, substr) && q.type != '\'')
			substr = expand(shell, substr + 1);
		else if (is_fake_var(shell, substr))
			substr = ft_strdup("");
		new_str = ft_strjoin(new_str, substr);
		free(substr);
		if(str[i] == q.type && !q.q_closed)
			q.q_closed = true;
		i += len;
	}
	return (new_str);
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
		var = convert_str(shell, tmp);
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
