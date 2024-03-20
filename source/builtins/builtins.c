/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/20 14:24:39 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//if (!copy_envp(shell, envp))
//	return (false);

/* 
bool	copy_envp(t_shell *shell, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	shell->envp = malloc(sizeof(char *) * (len + 1));
	if (!shell->envp)
		return (false);
	while (i < len)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
			return (false);
		i++;
	}
	shell->envp[i] = NULL;
	return (true);
}
 */

//	envp_into_list(shell->envp, shell->env_list);
//	while (shell->env_list)
//	{
//		printf("%s\n", shell->env_list->content);
//		shell->env_list = shell->env_list->next;
//	}

char	*get_path(t_shell *shell)
{
	int		i;
	char	*path;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(shell->envp[i] + 5);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

//check if command is a builtin, i is the index of the command
bool	is_builtin(t_shell *shell, int i)
{
	if (ft_strncmp(shell->cmds[i].args[0], "echo", 5) == 0 || \
		ft_strncmp(shell->cmds[i].args[0], "cd", 3) == 0 || \
		ft_strncmp(shell->cmds[i].args[0], "pwd", 4) == 0 || \
		ft_strncmp(shell->cmds[i].args[0], "export", 7) == 0 || \
		ft_strncmp(shell->cmds[i].args[0], "unset", 6) == 0 || \
		ft_strncmp(shell->cmds[i].args[0], "env", 4) == 0 || \
		ft_strncmp(shell->cmds[i].args[0], "exit", 5) == 0)
		return (true);
	return (false);
}
