/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:23 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/15 13:27:51 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//copy_pipes tp shell->cmds while securing their integrity
void	copy_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size)
	{
		if (i == 0 && shell->cmds[i].output == -1)
			shell->cmds[i].output = shell->pipes[i][1];
		else if (i == shell->size - 1 && shell->cmds[i].input == -1)
			shell->cmds[i].input = shell->pipes[i - 1][0];
		else
		{
			if (shell->cmds[i].output == -1)
				shell->cmds[i].output = shell->pipes[i][1];
			if (shell->cmds[i].input == -1)
				shell->cmds[i].input = shell->pipes[i - 1][0];
		}
		i++;
	}
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

void	handle_exitcode(t_shell *shell, int i, int status)
{
	if (shell->cmds[i].path)
	{
		if (WIFEXITED(status))
			shell->exitcode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exitcode = WTERMSIG(status) + 128;
	}
}

void	simple_child(t_shell *shell)
{
	redirect(shell, shell->cmds[0].input, shell->cmds[0].output);
	if (execve(shell->cmds[0].path, shell->cmds[0].args, shell->envp) == -1)
	{
		free_iter(shell);
		error_msg(shell, NULL);
	}
	free_pipes(shell);
	exit(1);
}
