/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/06 12:40:18 by jseidere         ###   ########.fr       */
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
void	minishell(char **envp, t_list *env_list)
{
	char	*input;

	env_list = NULL;
	envp_into_list(envp, env_list);
	while (true)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (input)
		{
			check_input(input);
			if (strcmp(input, "history -c") == 0)
				rl_clear_history();
			add_history(input);
			free(input);
		}
		else
			break ;
	}
}
