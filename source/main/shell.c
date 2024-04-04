/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/04 13:43:19 by jseidere         ###   ########.fr       */
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
			command_handler(shell, shell->cmds);
			if (!create_pipes(shell))
				return (free_iter(shell), error_msg(NULL), EXIT_FAILURE);
			if (!execute(shell))
				return (free_iter(shell), error_msg(NULL), shell->exitcode);
			free_iter(shell);
		}
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

//free things needed to be freed after every iteration
//TODO: unlink heredocs
void	free_iter(t_shell *shell)
{
	int	i;

	printf("free_iter\n");
	if (shell->input)
		free(shell->input);
	if (shell->norm_input)
		free(shell->norm_input);
	i = 0;
	free_tokens(shell->tokens);
	free_cmds(shell);
	free_pipes(shell);
	if (shell->child_pids)
		free(shell->child_pids);
}

//free the shell
void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	printf("free_shell\n");
	if (shell->envp && shell->envp[i])
		ft_free_list(shell->env_list);
	if (shell->paths)
	{
		while (shell->paths[i])
		{
			free(shell->paths[i]);
			i++;
		}
		free(shell->paths);
	}
	free(shell);
}
