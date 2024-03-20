/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:55:44 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/20 12:50:25 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//close all the pipes created, free pipes, and free the pipe array
//also close infile and outfile
//there is shell->size - 1 pipes
bool	close_all_fds(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->pipes)
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
