/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/12 13:40:52 by jkoupy           ###   ########.fr       */
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
		{
			shell->input = readline(PROMPT);
			if(!shell->input)
				exit_ctrl_d(shell);
		}
		else
		{
			line = get_next_line(fileno(stdin));
			shell->input = ft_strtrim(line, "\n");
			if (!shell->input)
				break ;
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
//exit if ctrl+d
void	exit_ctrl_d(t_shell *shell)
{
		printf("exit\n");
		free_shell(shell);
		exit(shell->exitcode);
}

bool	read_line(t_shell *shell)
{
	shell->input = readline(PROMPT);
	return (shell->input);
}
