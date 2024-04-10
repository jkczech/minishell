/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/10 15:49:53 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//main shell loop, that reads input, checks it and executes it
//TODO: error handling
int	minishell(t_shell *shell)
{
	while (true)
	{
		init_iter(shell);
		shell->input = readline(PROMPT);
		if (!shell->input)
			break ;
		signal(SIGINT, signal_handler);
		if (*shell->input)
		{
			add_history(shell->input);
			check_input(shell);
			parse(shell);
			if (shell->size > 1 && !create_pipes(shell))
				return (free_iter(shell), error_msg(NULL), EXIT_FAILURE);
			if (shell->size == 1 && !execute_simple(shell))
				return (free_iter(shell), error_msg(NULL), shell->exitcode);
			else if (shell->size > 1 && !execute_pipeline(shell))
				return (free_iter(shell), error_msg(NULL), shell->exitcode);
			free_iter(shell);
		}
	}
	return (EXIT_SUCCESS);
}

//not sure in which cases this was necessary - for norm I deleted it
//it was after parse()
//
// if (shell->size == 1 && !shell->cmds[0].path && !is_builtin(shell, 0))
// {
// 	free_iter(shell);
// 	continue ;
// }
