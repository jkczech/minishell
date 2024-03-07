/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/07 10:29:32 by jkoupy           ###   ########.fr       */
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
//void minishell(t_shell shell)
void	minishell(t_shell *shell)
{
	//char	*input;

	shell->env_list = NULL;
	envp_into_list(shell->envp, shell->env_list);
	while (true)
	{
		shell->input = readline(PROMPT);
		if (!shell->input)
			break ;
		if (shell->input)
		{
			check_input(shell);
			if (strcmp(shell->input, "history -c") == 0)
				rl_clear_history();
			add_history(shell->input);
			free(shell->input);
		}
		else
			break ;
	}
}
