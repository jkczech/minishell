/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:22:50 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/19 15:24:00 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//prints all attributes of a cmd
void    print_cmd(t_cmd *cmd)
{
    int i;

    i = 0;
    printf("--------------------\n");
    printf("cmd->input = %d\n", cmd->input);
    printf("cmd->output = %d\n", cmd->output);
    printf("cmd->args = ");
    while (cmd->args[i])
    {
        printf("%s ", cmd->args[i]);
        i++;
    }
    printf("\n");
    printf("--------------------\n");
}