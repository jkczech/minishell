/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:35:37 by jakob             #+#    #+#             */
/*   Updated: 2024/05/07 14:20:07 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//finds a variable in the environment
bool	find_var(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;

	node = shell->env_list;
	while (node)
	{
		var = ((t_env *)node->content)->var;
		if (ft_strncmp(var, str, ft_strlen(str)) == 0)
			return (true);
		node = node->next;
	}
	return (false);
}

//strlen before a non alpha character
int	strlen_b_sc(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		i++;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

//strlen before a character
int	strlen_before_a(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isalpha(str[i]) && str[i] != '$')
		i++;
	return (i);
}

//checks if a string is a environment variable
bool	is_var(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (find_var(shell, str + i + 1))
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

//checks if a string is a fake environment variable
//TODO: if not needed delete
bool	is_fake_var(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!find_var(shell, str + i + 1))
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}
