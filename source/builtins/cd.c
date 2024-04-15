/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:35:34 by jakob             #+#    #+#             */
/*   Updated: 2024/04/15 13:31:41 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Change directory to the specified path
void cd_forward(t_shell *shell, char *path)
{
    char *tmp;

    tmp = getcwd(NULL, 0);
    path = ft_strjoin3(tmp, "/", path);
    if(chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        shell->exitcode = 1;
    }
}

void cd_back(t_shell *shell)
{
    if(chdir("..") == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd("No such file or directory\n", 2);
        shell->exitcode = 1;
    }
}

void cd_home(t_shell *shell)
{
    char *home = get_env_value(shell, "HOME");

    if(home == NULL)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        shell->exitcode = 1;
    }
    else
        cd_forward(shell, home);
}

void cd_command(t_shell *shell, t_cmd *cmd)
{
    if(cmd->args[1] == NULL)
        cd_home(shell);
    else if(cmd->args[1])
        cd_forward(shell, cmd->args[1]);
    else if(ft_strncmp(cmd->args[1], "..", 2) == 0)
        cd_back(shell);
    else
    {
        char *cwd = getcwd(NULL, 0);
        char *path = ft_strjoin(cwd, "/");
        char *new_path = ft_strjoin(path, cmd->args[1]);
        cd_forward(shell, new_path);
        free(cwd);
        free(path);
        free(new_path);
    }
}
