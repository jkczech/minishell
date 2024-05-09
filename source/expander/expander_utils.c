/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:35:37 by jakob             #+#    #+#             */
/*   Updated: 2024/05/09 11:03:05 by jkoupy           ###   ########.fr       */
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
int	var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '$')
		i++;
	return (i);
}

//strlen before a character
int	len_until_dollar(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		len++;
	}
	return (len);
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

//checks if a string is a possible variable
//check if it is expandable
bool	is_possible_var(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '$')
		return (false);
	i++;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
