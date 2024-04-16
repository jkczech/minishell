/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/16 02:25:53 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//main shell loop, that reads input, checks it and executes it
//TODO: error handling
void	minishell(t_shell *shell)
{
	while (true)
	{
		init_iter(shell);
		if (!read_line(shell))
			break ;
		if (*shell->input)
		{
			check_input(shell);
			parse(shell);
			if (shell->size > 1 && !create_pipes(shell))
				return (free_iter(shell), error_msg(NULL));
			if (shell->size == 1 && !execute_simple(shell))
				return (free_iter(shell), error_msg(NULL));
			else if (shell->size > 1 && !execute_pipeline(shell))
				return (free_iter(shell), error_msg(NULL));
			add_history(shell->input);
			free_iter(shell);
		}
	}
}

//not sure in which cases this was necessary - for norm I deleted it
//it was after parse()
//
// if (shell->size == 1 && !shell->cmds[0].path && !is_builtin(shell, 0))
// {
// 	free_iter(shell);
// 	continue ;
// }

bool	read_line(t_shell *shell)
{
	shell->input = readline(PROMPT);
	return (shell->input);
}