/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:23:37 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/13 14:47:28 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Exit shell with exit status
void    exit_shell_status(t_shell *shell, int status)
{
    free_shell(shell);
    exit(status);
}

//Exit error message
void exit_error_msg(t_shell *shell, char *msg, char *cmd, int status)
{
    ft_putstr_fd("exit\n", 2);
    printf("%s exit: %s: %s\n", PROMPT, cmd, msg);
    exit_shell_status(shell, status);
}

//Exit shell without exit status
void    easy_exit(t_shell *shell)
{
    printf("exit\n");
    if(shell)
        free_shell(shell);
    exit(0);
}

//check if exit command is called
void   exit_command(t_shell *shell)
{
    char **args;

    args = NULL;
    
    if(strcmp(shell->input, "exit") == 0)
        easy_exit(shell);
    else
        args = convert_input(shell);

    if(strcmp(args[0], "exit") == 0)
    {
        if(!check_amount_of_args(args))
            exit_error_msg(shell, "too many arguments", NULL, 1);
        if(!is_numeric(args[1]))
            exit_error_msg(shell, "numeric argument required", args[1], 255);
        easy_exit(shell);
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