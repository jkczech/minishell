/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/20 14:30:49 by jkoupy           ###   ########.fr       */
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

//main shell loop, read input, check it and execute it
//TODO: free input into free_shell
//TODO: error handling
//TODO: exit_command() into execute()
int	minishell(t_shell *shell)
{
	while (true)
	{
		shell->input = readline(PROMPT);
		if (!shell->input)
			break ;
		if (shell->input)
		{
			add_history(shell->input);
			check_input(shell);
			parse(shell);
			exit_command(shell);
			if (!create_pipes(shell))
				return (free_pipex(shell), error_msg(NULL), EXIT_FAILURE);
			if (!execute(shell))
				return (free_pipex(shell), error_msg(NULL), shell->exitcode);
			free_iter(shell);
		}
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

//free things needed to be freed after every iteration
void	free_iter(t_shell *shell)
{
	if (shell->input && strcmp(shell->input, "exit") != 0)
		free(shell->input);
	if (shell->norm_input)
		free(shell->norm_input);
	free_tokens(shell->tokens);
	free_cmds(shell);
}
