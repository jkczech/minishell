/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:35:34 by jakob             #+#    #+#             */
/*   Updated: 2024/05/14 11:36:48 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Change directory to the specified path
void	cd_forward(t_shell *shell, char *path)
{
	char	*tmp;
	char	*cwd;

	tmp = getcwd(NULL, 0);
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
			cd_error(shell, path);
	}
	else
	{
		cwd = ft_strjoin3(tmp, "/", path);
		if (chdir(path) == -1)
		{
			cd_error(shell, path);
		}
		free(cwd);
	}
	free(tmp);
}

void	cd_back(t_shell *shell, char *path)
{
	char	*tmp;
	char	*cwd;
	int		len;
	
	tmp = get_env_value(shell, "PWD");
	if(!tmp)
		return ;
	cwd = ft_strjoin("..", tmp);
	
	len = ft_strlen(cwd);
	if (chdir(path) == -1)
	{
		cd_error(shell, path);
		if(ft_strncmp(path, cwd, len) != 0)
			free(path);
	}
	free(tmp);
	free(cwd);
}

void	cd_home(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		shell->exitcode = 1;
	}
	else
		cd_forward(shell, home);
}

void	cd_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("MiNiSHell: cd: too many arguments\n", 2);
		shell->exitcode = 1;
		return ;
	}
	if (cmd->args[1] == NULL)
		cd_home(shell);
	else if (ft_strncmp(cmd->args[1], "..", 2) == 0)
		cd_back(shell, cmd->args[1]);
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		cd_oldpwd(shell);
	else if (cmd->args[1])
		cd_forward(shell, cmd->args[1]);
	update_pwd_n_oldpwd(shell);
}

//get env var
char	*get_env_var(t_shell *shell, char *var)
{
	t_list	*tmp;
	int		len;

	tmp = shell->env_list;
	len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->var, var, len) == 0)
			return (((t_env *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (NULL);
}
// unset PWD 
// cd ..
// beschreibt pwd 