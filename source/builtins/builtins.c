/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/19 20:59:53 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Get the path from the environment variables
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

//execute builtins
bool	builtin_handler(t_shell *shell, int i)
{
	t_cmd	*cmd;

	cmd = shell->cmds + i;
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_command(shell, cmd);
	else if (ft_strncmp(shell->cmds[i].args[0], "exit", 5) == 0)
		exit_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_command(shell, cmd);
	return (true);
}
	/*
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_command(shell, cmd);
	else
		other_command(shell, cmd); */

bool	is_builtin(t_shell *shell, int i)
{
	if (!shell->cmds || !shell->cmds[i].args || !shell->cmds[i].args[0])
		return (false);
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
