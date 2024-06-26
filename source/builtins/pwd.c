/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:38:07 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/14 20:16:43 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Prints the current working directory
void	pwd_command(t_shell *shell, t_cmd *cmd, int out)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error");
		shell->exitcode = 1;
		return ;
	}
	ft_putstr_fd(cwd, out);
	ft_putstr_fd("\n", out);
	free(cwd);
	shell->exitcode = 0;
}
