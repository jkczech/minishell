/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:23:37 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/15 15:50:07 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Exit shell with exit status
void	exit_shell_status(t_shell *shell, int status)
{
	ft_putstr_fd("exit\n", 2);
	free_shell(shell);
	printf("Exit status: %d\n", status);
	exit(status);
}

//Exit error message
void	exit_error_msg(t_shell *shell, char *msg, char *cmd, int status)
{
	ft_putstr_fd("exit\n", 2);
	printf("%s exit: %s: %s\n", PROMPT, cmd, msg);
	exit_shell_status(shell, status);
}

//Exit shell without exit status
//Needed to safe exitcode before freeing shell
void	easy_exit(t_shell *shell, int status)
{
	free_iter(shell);
	ft_putstr_fd("exit\n", 2);
	if (shell)
		free_shell(shell);
	printf("Exit status: %d\n", status);
	exit(status);
}

//check if exit command is called
void	exit_command(t_shell *shell, t_cmd *cmd)
{
	int exit_status;

	exit_status = shell->exitcode;
	//printf("Command: %s\n", cmd->args[0]);
	if (cmd && ft_strncmp(cmd->args[0], "exit", 4) == 0)
	{
		if(!cmd->args[1])
			easy_exit(shell, exit_status);
		else if (cmd->args[1] && !cmd->args[2])
		{
			if (!is_numeric(cmd->args[1]))
				exit_error_msg (shell, "numeric argument required", cmd->args[1], 255);
			else
				exit_shell_status(shell, ft_atoi(cmd->args[1]));
		}
		else if(is_numeric(cmd->args[1]) && !is_numeric(cmd->args[2]))
		{
			ft_putstr_fd("exit\n", 2);
			printf("%s exit: to many arguments\n", PROMPT);
			shell->exitcode = 1;
		}
	}
}

//Possible cases for exit command
// Overflow
// Underflow
// Invalid argument
// No argument
// Multiple arguments
// Exit status
// Exit status with argument
// Non-numeric argument