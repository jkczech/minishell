/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/21 16:05:57 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//init path in pipex
bool	init_path(t_shell *shell)
{
	char	*path;

	path = get_path(shell);
	if (!path)
		return (false);
	shell->paths = ft_split(path, ':');
	if (path)
		free(path);
	if (!shell->paths)
		return (false);
	return (true);
}

//init all the shell variables
bool	init_shell(t_shell *shell, char **envp)
{
	shell->input = NULL;
	shell->norm_input = NULL;
	shell->tokens = NULL;
	shell->history = NULL;
	shell->envp = envp;
	init_path(shell);
	return (true);
}

//Count the number of arguments
int	args_counter(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

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

// command handler
void	command_handler(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_command(shell, cmd);
}
/*	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_command(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_command(shell, cmd);
	else
		other_command(shell, cmd); */
