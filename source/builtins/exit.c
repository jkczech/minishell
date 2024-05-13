/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:23:37 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/13 16:48:35 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Exit shell with exit status
void	exit_shell_status(t_shell *shell, int status)
{
	free_iter(shell);
	free_shell(shell);
	exit(status);
}

//exit error message, not exiting
void	exit_error_msg(char *msg, char *cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

//exit shell without exit status
//needed to safe exitcode before freeing shell
void	easy_exit(t_shell *shell, int status)
{
	free_iter(shell);
	ft_putstr_fd("exit\n", 2);
	if (shell)
		free_shell(shell);
	exit(status);
}

//Exit with argument
void	exit_argument(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[2] && cmd->args[1] && is_numeric(cmd->args[1]))
	{
		exit_error_msg("too many arguments", cmd->args[1]);
		shell->exitcode = 1;
	}
	else if (!is_numeric(cmd->args[1]) || !check_overflow(cmd->args[1]))
	{
		exit_error_msg("numeric argument required", cmd->args[1]);
		shell->exitcode = 2;
	}
	else
		easy_exit(shell, convert_exit_status(cmd));
}

//check if exit command is called
void	exit_command(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		easy_exit(shell, shell->exitcode);
	if (!cmd->args[1] || !cmd->args[1][0])
		easy_exit(shell, shell->exitcode);
	else if (cmd->args[1])
		exit_argument(shell, cmd);
}

// Test if exit command is called
// exit 123 (normal exit)
// exit -123 (negative exit, Underflow)
// exit 256 (Overflow)
// exit 123 123 (to many arguments)
// exit asd (non numeric argument)
// exit 123 asd  (to many arguments) not exiting
// exit "" (no argument, Exitstatus 2) 
// 	|-> 🤏🐚:  exit: "": numeric argument required but should be without quotes
// exit 00000123 (normal exit with exit status 123)
// exit +123 (normal exit with exit status 123)
// Str + C = 130 Exit status