/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:41:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/26 12:48:57 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//redirect input to stdin and output to stdout
//close input and output fds of all other unused pipes in current process
void	redirect(t_shell shell, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		free_iter(&shell);
		exit(1);
	}
	if (input != STDIN_FILENO)
		close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		free_iter(&shell);
		exit(1);
	}
	if (output != STDOUT_FILENO)
		close(output);
}

//handling different kinds of child processes, first, middle, last
void	children(t_shell pipex, int i)
{
	if (!pipex.cmds[i].found)
	{
		free_iter(&pipex);
		exit(1);
	}
	if (i == 0 && pipex.size == 1)
		child(pipex, i, pipex.cmds[i].input, pipex.cmds[i].output);
	else if (i == 0)
		child(pipex, i, pipex.cmds[i].input, pipex.pipes[i][1]);
	else if (i != pipex.size - 1)
		child(pipex, i, pipex.pipes[i - 1][0], pipex.pipes[i][1]);
	else
		child(pipex, i, pipex.pipes[i - 1][0], pipex.cmds[i].output);
}

//handle child processes, execute commands, else error message
void	child(t_shell pipex, int i, int input, int output)
{
	if (input != STDIN_FILENO && output != STDOUT_FILENO)
		redirect(pipex, input, output);
	free_pipes(&pipex);
	if (execve(pipex.cmds[i].path, pipex.cmds[i].args, pipex.envp) == -1)
	{
		free_iter(&pipex);
		error_msg(NULL);
	}
	exit(1);
}
