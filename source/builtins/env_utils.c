/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:21:18 by jakob             #+#    #+#             */
/*   Updated: 2024/05/15 16:20:19 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_env_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**envp_list_into_char(t_list *env_list)
{
	t_list	*tmp;
	char	**envp;
	int		i;

	tmp = env_list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i] = ft_strjoin3(((t_env *)env_list->content)->var, "=",
				((t_env *)env_list->content)->value);
		if (!envp[i++])
			return (NULL);
		env_list = env_list->next;
	}
	envp[i] = NULL;
	return (envp);
}
