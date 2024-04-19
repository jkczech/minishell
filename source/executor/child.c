/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:41:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/19 15:26:28 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//redirect input to stdin and output to stdout
//close input and output fds of all other unused pipes in current process
void	redirect(t_shell *shell, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		free_iter(shell);
		exit(1);
	}
	if (input != STDIN_FILENO)
		close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		free_iter(shell);
		exit(1);
	}
	if (output != STDOUT_FILENO)
		close(output);
}

//handle child processes, execute commands, else error message
void	child(t_shell *shell, int i, int input, int output)
{
	redirect(shell, input, output);
	free_pipes(shell);
	if (is_builtin(shell, i))
	{
		builtin_handler(shell, i);
		exit(shell->exitcode);
	}
	if (!shell->cmds[i].path)
		free_iter(shell);
	else if (execve(shell->cmds[i].path,
			shell->cmds[i].args, shell->envp) == -1)
	{
		free_iter(shell);
		error_msg(NULL);
	}
	exit(1);
}
