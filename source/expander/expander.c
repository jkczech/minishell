/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/17 12:37:05 by jakob            ###   ########.fr       */
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

//converts a string with variables to a string with values
char	*convert_str(t_shell *shell, char *str)
{
	char	*substr;
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '$')
			len = strlen_b_sc(str + i);
		else
			len = strlen_before_a(str + i);
		substr = ft_substr(str, i, len);
		if (ft_strncmp(substr, "$?", 2) == 0)
			substr = ft_strdup(ft_itoa(shell->exitcode));
		if (!substr)
			return (NULL);
		if (is_var(shell, substr))
			substr = expand(shell, substr + 1);
		else if (is_fake_var(shell, substr))
			substr = ft_strdup("");
		if (!substr)
			return (NULL);
		new_str = ft_strjoin(new_str, substr);
		if (!new_str)
		{
			free(substr);
			return (NULL);
		}
		free (substr);
		i += len;
	}
	return (new_str);
}

//expands variables in the tokens
void	expander(t_shell *shell)
{
	char	*tmp;
	t_token	*token;
	char	*var;

	token = *shell->tokens;
	while (token)
	{
		tmp = token->content;
		var = convert_str(shell, tmp);
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
//