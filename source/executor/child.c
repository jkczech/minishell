/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:41:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/26 16:20:11 by jkoupy           ###   ########.fr       */
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
void	children(t_shell shell, int i)
{
	if (!shell.cmds[i].args)
	{
		free_iter(&shell);
		exit(1);
	}
	if (i == 0 && shell.size == 1)
		child(shell, i, shell.cmds[i].input, shell.cmds[i].output);
	else if (i == 0)
		child(shell, i, shell.cmds[i].input, shell.pipes[i][1]);
	else if (i != shell.size - 1)
		child(shell, i, shell.pipes[i - 1][0], shell.pipes[i][1]);
	else
		child(shell, i, shell.pipes[i - 1][0], shell.cmds[i].output);
}

//handle child processes, execute commands, else error message
void	child(t_shell shell, int i, int input, int output)
{
	if (input != STDIN_FILENO && output != STDOUT_FILENO)
		redirect(shell, input, output);
	free_pipes(&shell);
	builtin_handler(&shell, &shell.cmds[i]);
	if (execve(shell.cmds[i].path, shell.cmds[i].args, shell.envp) == -1)
	{
		free_iter(&shell);
		error_msg(NULL);
	}
	exit(1);
}
