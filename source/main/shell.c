/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/11 12:00:34 by jseidere         ###   ########.fr       */
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
	shell->env_list = NULL;
	envp_into_list(shell->envp, shell->env_list);
	while(shell->env_list)
	{
		printf("%s\n", shell->env_list->content);
		shell->env_list = shell->env_list->next;
	}
	while (true)
	{
		shell->input = readline(PROMPT);
		if (!shell->input)
			break ;
		if (shell->input)
		{
			if(strcmp(shell->input, "exit") == 0)
				exit_shell(shell);
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
