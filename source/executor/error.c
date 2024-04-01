/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:46:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/01 18:16:49 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//printing error in the zsh format (also lower capitalized)
void	error_msg(char *file)
{
	char	*message;

	ft_putstr_fd("shell: ", 2);
	message = ft_strdup(strerror(errno));
	message = ft_strlwr(message);
	if (message)
		ft_putstr_fd(message, 2);
	else
		ft_putstr_fd("error allocating error message", 2);
	if (file)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
	}
	ft_putstr_fd("\n", 2);
	if (message)
		free(message);
}

//prints a bash like error message
void	cmd_not_found(t_shell *pipex, int i)
{
	ft_putstr_fd("shell: command not found: ", 2);
	ft_putstr_fd(pipex->cmds[i].args[0], 2);
	ft_putstr_fd("\n", 2);
}
