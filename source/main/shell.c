/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/03 23:25:36 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	envp_into_list(char **envp, t_list *env_list)
// {
// 	int	i;

// 	i = 0;
// 	env_list = NULL;
// 	while (envp[i])
// 	{
// 		ft_lstadd_back(&env_list, ft_lstnew(envp[i]));
// 		i++;
// 	}
// }

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
		if (*shell->input)
		{
			add_history(shell->input);
			check_input(shell);
			parse(shell);
			if (shell->size == 1 && (!shell->cmds[0].path) && !is_builtin(shell, 0))
			{
				free_iter(shell);
				continue ;
			}
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
