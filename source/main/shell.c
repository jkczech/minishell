/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/12 13:02:43 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	envp_into_list(char **envp, t_list *env_list)
{
	int	i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(envp[i]));
		i++;
	}
}

//main shell loop, that reads input, checks it and executes it
void	minishell(t_shell *shell)
{
	while (true)
	{
		shell->input = readline(PROMPT);
		if (!shell->input)
			break ;
		if (shell->input)
		{
			if(strcmp(shell->input, "exit") == 0)
				easy_exit(shell);
			check_input(shell);
			if (strcmp(shell->input, "history -c") == 0)
			{
				rl_clear_history();
				free(shell->input);
				continue ;
			}
			add_history(shell->input);
			check_input(shell);
			parse(shell);
			//execute(shell);
			free(shell->input);
		}
		else
			break ;
	}
}
