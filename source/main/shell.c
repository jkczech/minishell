/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/19 20:27:18 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//main shell loop, that reads input, checks it and executes it
//TODO: error handling
void	minishell(t_shell *shell)
{
	while (true)
	{
		set_signals();
		init_iter(shell);
		if (!read_line(shell))
			break ;
		if (check_input(shell) && parse(shell))
			execute(shell);
		add_history(shell->input);
		free_iter(shell);
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
