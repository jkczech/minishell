/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/12 11:25:32 by jkoupy           ###   ########.fr       */
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
			get_size(shell);
			execute(shell);
		}
		else
			break ;
	}
}

void	get_size(t_shell *shell)
{
	t_token	*token;
	int		size;

	token = *(shell->tokens);
	if (!token)
		return ;
	size = 0;
	while (token)
	{
		if (token->token == PIPE)
			size++;
		token = token->next;
	}
	shell->size = size + 1;
}
