/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:38:07 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/22 11:51:31 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Prints the current working directory
void	pwd_command(t_shell *shell, t_cmd *cmd)
{
    char	*cwd;

    (void)cmd;
    cwd = getcwd(NULL, 0);
    if(!cwd)
    {
        perror("Error");
        shell->exitcode = 1;
        return ;
    }
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);
    free(cwd);
    shell->exitcode = 0;
}
