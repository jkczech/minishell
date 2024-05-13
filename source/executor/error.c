/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:46:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/13 13:59:51 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//printing error in the bash format
void	error_msg(t_shell *shell, char *file)
{
	char	*message;

	if (errno == 0)
		return ;
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
	shell->exitcode = 1;
}

//prints a bash like error message
bool	cmd_not_found(t_shell *shell, int i)
{
	ft_putstr_fd(ERR_PROMPT, 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(shell->cmds[i].args[0], 2);
	ft_putstr_fd("\n", 2);
	shell->exitcode = 127;
	return (true);
}

void	cd_error(t_shell *shell, char *path)
{
	ft_putstr_fd("MiNiSHell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	shell->exitcode = 1;
}
