/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:46:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/16 03:36:29 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//printing error in the bash format
void	error_msg(char *file)
{
	char	*message;

	ft_putstr_fd(ERR_PROMPT, 2);
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
bool	cmd_not_found(t_shell *shell, int i)
{
	ft_putstr_fd(ERR_PROMPT, 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(shell->cmds[i].args[0], 2);
	ft_putstr_fd("\n", 2);
	return (true);
}
