/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:41:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/15 19:31:30 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//redirect input to stdin and output to stdout
//close input and output fds of all other unused pipes in current process
void	redirect(t_shell *shell, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
		frexit(shell, 1);
	if (input != STDIN_FILENO)
		close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
		frexit(shell, 1);
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
		free_iter(shell);
		free_shell(shell);
		exit(shell->exitcode);
	}
	mode(shell, CHILD);
	if (!shell->cmds[i].path)
		free_iter(shell);
	else if (execve(shell->cmds[i].path,
			shell->cmds[i].args, shell->envp) == -1)
	{
		free_iter(shell);
		error_msg(shell, NULL);
	}
	free_shell(shell);
	exit(1);
}
