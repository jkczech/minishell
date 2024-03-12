/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:34:49 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/12 10:47:22 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//create all pipes needed
//pipex.pipes is not NULL terminated
bool	create_pipes(t_shell *pipex)
{
	int	i;

	i = 0;
	pipex->pipes = malloc((pipex->size) * sizeof(int *));
	if (!pipex->pipes)
		return (false);
	while (i < pipex->size)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
			return (false);
		if (pipe(pipex->pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

//waiting for all the child processes to finish
//todo - exitcode handling
/* if (pipex->outfile == -1)
		pipex->exitcode = 1;
	else if (!pipex->cmds[i - 1].found)
		pipex->exitcode = 127;
	else
		pipex->exitcode = 0; */
bool	wait_pids(t_shell *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size && pipex->child_pids[i] > 0)
	{
		waitpid(pipex->child_pids[i], NULL, 0);
		i++;
	}
	return (true);
}

//allocate array of ints for the pids of child processes
bool	allocate_pids(t_shell *pipex)
{
	int	i;

	pipex->child_pids = malloc(pipex->size * sizeof(int));
	if (!pipex->child_pids)
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pipex->child_pids[i] = -1;
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
			return (close_all_fds(shell), false);
		i++;
	}
	close_all_fds(shell);
	wait_pids(shell);
	return (true);
}
