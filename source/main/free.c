/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:08:25 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/28 12:04:48 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>

//free things needed to be freed after every iteration
//TODO: unlink heredocs
void	free_iter(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->norm_input)
		free(shell->norm_input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmds(shell);
	if (shell->pipes)
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

//free the commands table
void	free_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size && shell->cmds && shell->cmds[i].args)
	{
		if (shell->cmds[i].args)
			free_array(shell->cmds[i].args);
		if (shell->cmds[i].path)
			free(shell->cmds[i].path);
		i++;
	}
	free(shell->cmds);
}

//free all elements of an array of strings including the array itself
//needs to be NULL terminated
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

//close all the pipes created, free pipes, and free the pipe array
//also close infile and outfile
//there is shell->size - 1 pipes
bool	free_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->pipes || shell->size == 1)
		return (false);
	while (i < shell->size - 1 && shell->pipes[i])
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		if (shell->pipes[i])
			free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	return (true);
}
