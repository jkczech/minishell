/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:23:37 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/20 12:49:15 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Exit shell with exit status
void	exit_shell_status(t_shell *shell, int status)
{
	free_shell(shell);
	exit(status);
}

//Exit error message
void	exit_error_msg(t_shell *shell, char *msg, char *cmd, int status)
{
	ft_putstr_fd("exit\n", 2);
	printf("%s exit: %s: %s\n", PROMPT, cmd, msg);
	exit_shell_status(shell, status);
}

//exit shell without exit status
void	easy_exit(t_shell *shell)
{
	free_iter(shell);
	printf("exit\n");
	if (shell)
		free_shell(shell);
	exit(shell->exitcode);
}

//check if exit command is called
void	exit_command(t_shell *shell)
{
	// char	**args;

	// args = NULL;
	if (shell->input && ft_strncmp(shell->input, "exit", 4) == 0)
		easy_exit(shell);
	// else
	// 	args = convert_input(shell);
	// if (args[0] && strcmp(args[0], "exit") == 0)
	// {
	// 	if (!check_amount_of_args(args))
	// 		exit_error_msg (shell, "too many arguments", NULL, 1);
	// 	if (!is_numeric(args[1]))
	// 		exit_error_msg (shell, "numeric argument required", args[1], 255);
	// 	free_array(args);
	// 	easy_exit(shell);
	// }
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