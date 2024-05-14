/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:22:50 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 20:10:28 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//prints all attributes of a cmd
void	print_cmd(t_cmd *cmd)
{
	int	i;

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

//print cmd list
//index, content, input, output
void	print_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->size)
	{
		printf("\033[1mCommands:\n\033[0mindex: %d\nargs: ", i);
		j = 0;
		if (!shell->cmds[i].args)
			printf("null %c\n", i);
		while (shell->cmds[i].args && shell->cmds[i].args[j])
			printf("\033[0;32m%s\033[0m ", shell->cmds[i].args[j++]);
		if (!shell->cmds[i].args || !shell->cmds[i].args[0])
			printf("(null)");
		printf("\n");
		if (shell->cmds[i].input == STDIN_FILENO)
			printf("input: %d (STD)\n", shell->cmds[i].input);
		else
			printf("input: %d\n", shell->cmds[i].input);
		if (shell->cmds[i].output == STDOUT_FILENO)
			printf("output: %d (STD)\n", shell->cmds[i].output);
		else
			printf("output: %d\n", shell->cmds[i].output);
		printf("\n");
	}
}
