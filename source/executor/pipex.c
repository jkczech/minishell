/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:34:49 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/13 15:34:36 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute(t_shell *shell)
{
	if (shell->size > 1 && !create_pipes(shell))
		return (error_msg(shell, NULL), false);
	if (shell->size == 1 && !execute_simple(shell))
		return (error_msg(shell, NULL), false);
	else if (shell->size > 1 && !execute_pipeline(shell))
		return (error_msg(shell, NULL), false);
	return (true);
}

//create all pipes needed
//shell->size - 1 pipes are created
//shell->pipes is NOT NULL terminated
bool	create_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	shell->pipes = malloc((shell->size - 1) * sizeof(int *));
	if (!shell->pipes)
		return (false);
	while (i < shell->size - 1)
	{
		shell->pipes[i] = malloc(2 * sizeof(int));
		if (!shell->pipes[i])
			return (false);
		if (pipe(shell->pipes[i]) == -1)
			return (false);
		i++;
	}
	copy_pipes(shell);
	return (true);
}

//waiting for all the child processes to finish
//TODO: exitcode handling
bool	wait_pids(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size && shell->child_pids[i] > 0)
	{
		waitpid(shell->child_pids[i], NULL, 0);
		i++;
	}
	return (true);
}

//fork, pipe, execute in child processes
bool	execute_pipeline(t_shell *shell)
{
	int	pid;
	int	i;

	if (!allocate_pids(shell))
		return (false);
	i = 0;
	while (i < shell->size)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!shell->cmds[i].args)
			{
				free_iter(shell);
				exit(1);
			}
			child(shell, i, shell->cmds[i].input, shell->cmds[i].output);
		}
		else if (pid > 0)
			shell->child_pids[i] = pid;
		else
			return (free_pipes(shell), false);
		i++;
	}
	return (free_pipes(shell), wait_pids(shell), true);
}

//execute if there is only one command
//TODO: exitcode handling
bool	execute_simple(t_shell *shell)
{
	int	pid;

	if (shell->size != 1 || !shell->cmds || !shell->cmds[0].args)
		return (false);
	if (is_builtin(shell, 0))
		return (builtin_handler(shell, 0));
	pid = fork();
	if (pid == 0 && shell->cmds[0].path == NULL)
	{
		free_pipes(shell);
		exit(shell->exitcode);
	}
	if (pid == 0)
	{
		redirect(shell, shell->cmds[0].input, shell->cmds[0].output);
		if (execve(shell->cmds[0].path, shell->cmds[0].args, shell->envp) == -1)
			error_msg(shell, NULL);
		free_pipes(shell);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		return (false);
	return (free_pipes(shell));
}
