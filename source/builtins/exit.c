/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:23:37 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/06 11:11:26 by jseidere         ###   ########.fr       */
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
    perror("exit");
    printf("%s exit: %s: %s\n", PROMPT, cmd, msg);
    exit_shell_status(shell, status);
}

//Checks amount of arguments
bool check_amount_of_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    if (i > 2)
        return (false);
    return (true);
}


//Check if argument is numeric
bool is_numeric(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}


// Exit shell without exit status
void    exit_shell(t_shell *shell)
{
    free_shell(shell);
    exit(0);
}

void   exit_command(t_shell *shell, char **args)
{
    if(!args[1])
    {
        perror("exit");
        exit_shell(shell);
    }
    else if (!&check_amount_of_args)
    {
        if(!is_numeric(args[1]))
            exit_error_msg(shell, "numeric argument required\n", args[1], 2);
        else if (is_numeric(args[1]))
            exit_error_msg(shell, "too many arguments\n", NULL, 1);
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