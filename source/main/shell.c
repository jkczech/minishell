/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/14 12:05:38 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//main shell loop, that reads input, checks it and executes it
//TODO: error handling
// MAIN for testing	
void	minishell(t_shell *shell)
{
	char	*line;

	while (true)
	{
		mode(shell, EMPTY);
		init_iter(shell);
	/* 	if (!read_line(shell))
			break ; */
		if (isatty(fileno(stdin)))
			shell->input = readline(PROMPT);
		else
		{
			line = get_next_line(fileno(stdin));
			shell->input = ft_strtrim(line, "\n");
			if (!shell->input)
			{
				//break;
				free_shell(shell);
				free(line);
				exit(0);
			}
			free(line);
		}
		mode(shell, WRITTEN);
		if (g_sig == 1 && g_sig--)
			shell->exitcode = 130;
		if (!shell->input)
			exit_command(shell, NULL);
		if (check_input(shell) && parse(shell))
			execute(shell);
		add_history(shell->input);
		free_iter(shell);
	}
}

bool	read_line(t_shell *shell)
{
	shell->input = readline(PROMPT);
	return (shell->input);
}
