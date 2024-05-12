/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:35:05 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/12 18:02:22 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//copy two dimensional array
char	**copy_array(char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	while (arr[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		if (!ret[i])
		{
			free_array(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

//maybe delete
void	print_two_d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

//update env var SHLVL
void	update_shell_lvl(t_shell *shell)
{
	char	*env;
	char	*lvl;
	int		lvl_int;

	env = get_env_var(shell, "SHLVL");
	if (!env)
		return ;
	lvl_int = ft_atoi(env);
	if (lvl_int < 0)
		lvl_int = 0;
	lvl_int++;
	lvl = ft_itoa(lvl_int);
	if (!lvl)
		return ;
	set_env_var(shell, "SHLVL", lvl);
	free(lvl);
}

//update env var _
void	update_shell_(t_shell *shell)
{
	char	*env;

	env = get_env_var(shell, "_");
	set_env_var(shell, "_", "/usr/bin/env");
}
