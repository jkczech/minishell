/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/15 15:05:27 by jseidere         ###   ########.fr       */
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
//TODO: free input into free_shell
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
			exit_command(shell, shell->cmds);
			free_iter(shell);
		}
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

//frees things needed to be freed after every iteration
void	free_iter(t_shell *shell)
{
	if (shell->input && strcmp(shell->input, "exit") != 0)
		free(shell->input);
	if (shell->norm_input)
		free(shell->norm_input);
	free_tokens(shell->tokens);
	free_cmds(shell);
}

// if (!create_pipes(shell))
// 	return (free_pipex(shell), error_message(NULL), EXIT_FAILURE);
// printf("got here\n");
// if (!execute(shell))
// 	return (free_pipex(shell), error_message(NULL), shell->exitcode);
// printf("got here2\n");
// free_pipex(shell);
