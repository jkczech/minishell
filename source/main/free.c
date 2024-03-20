/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:08:25 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/20 12:56:24 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>

//free the shell
void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
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

//free allocated pipex elements, all cmds, paths
//close infile and outfile, unlink .here_doc
//TODO: change to shell, check
void	free_pipex(t_shell *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size && pipex->cmds && pipex->cmds[i].args)
	{
		free_array(pipex->cmds[i].args);
		if (pipex->cmds[i].found)
			free(pipex->cmds[i].path);
		i++;
	}
	free(pipex->cmds);
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->child_pids)
		free(pipex->child_pids);
	//if (pipex->heredoc)
	//	unlink(".here_doc");
	return ;
}

//free the commands table
void	free_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size)
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