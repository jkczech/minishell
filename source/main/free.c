/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:08:25 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/15 21:26:40 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>

//free things needed to be freed after every iteration
//pipes are freed in the parent process elsewhere
void	free_iter(t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	if (shell->input)
		free(shell->input);
	if (shell->norm_input)
		free(shell->norm_input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmds(shell);
	if (shell->child_pids)
		free(shell->child_pids);
	while (shell->hd_i > 0)
	{
		tmp2 = ft_itoa(shell->hd_i);
		tmp = ft_strjoin("heredocs/.heredoc", tmp2);
		unlink(tmp);
		free(tmp);
		free(tmp2);
		shell->hd_i--;
	}
}

//free the shell
void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->env_list)
		ft_free_list(shell->env_list);
	if (shell->envp)
		free_array(shell->envp);
	if (shell->paths)
	{
		while (shell->paths[i])
		{
			free(shell->paths[i]);
			i++;
		}
		free(shell->paths);
	}
	rl_clear_history();
}

//free the commands table
void	free_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size && shell->cmds)
	{
		if (shell->cmds[i].args)
			free_array(shell->cmds[i].args);
		if (shell->cmds[i].path)
			free(shell->cmds[i].path);
		if (shell->cmds[i].input != STDIN_FILENO
			&& shell->cmds[i].input != -1)
			close(shell->cmds[i].input);
		if (shell->cmds[i].output != STDOUT_FILENO
			&& shell->cmds[i].output != -1)
			close(shell->cmds[i].output);
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
//if size == 1, there is no pipe, but closes the input and output fds
//there is shell->size - 1 pipes
bool	free_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->pipes)
		return (true);
	while (i < shell->size - 1 && shell->pipes[i])
	{
		if (shell->pipes[i][1] != -1)
			close(shell->pipes[i][0]);
		if (shell->pipes[i][1] != -1)
			close(shell->pipes[i][1]);
		if (shell->cmds[i].input != -1
			&& shell->cmds[i].input != STDIN_FILENO)
			close(shell->cmds[i].input);
		if (shell->cmds[i].output != -1
			&& shell->cmds[i].output != STDOUT_FILENO)
			close(shell->cmds[i].output);
		if (shell->pipes[i])
			free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	return (true);
}
