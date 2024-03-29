/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:34:49 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/21 15:18:27 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (true);
}

/* if (shell->outfile == -1)
		shell->exitcode = 1;
	else if (!shell->cmds[i - 1].found)
		shell->exitcode = 127;
	else
		shell->exitcode = 0; */

//waiting for all the child processes to finish
//todo - exitcode handling
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

//allocate array of ints for the pids of child processes
bool	allocate_pids(t_shell *shell)
{
	int	i;

	shell->child_pids = malloc(shell->size * sizeof(int));
	if (!shell->child_pids)
		return (false);
	i = 0;
	while (i < shell->size)
	{
		shell->child_pids[i] = -1;
		i++;
	}
	return (true);
}

//fork, pipe, execute in child processes
bool	execute(t_shell *shell)
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
			children(*shell, i);
		else if (pid > 0)
			shell->child_pids[i] = pid;
		else
			return (false);
		i++;
	}
	return (wait_pids(shell), true);
}
