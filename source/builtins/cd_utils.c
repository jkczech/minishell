/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/09 11:11:12 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//set env var
void	set_env_var(t_shell *shell, char *var, char *value)
{
	t_list	*tmp;
	int		len;

	tmp = shell->env_list;
	len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->var, var, len) == 0)
		{
			((t_env *)tmp->content)->value = ft_strdup(value);
			if (!((t_env *)tmp->content)->value)
				((t_env *)tmp->content)->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
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

//cd old pwd
void	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_var(shell, "OLDPWD");
	if (oldpwd)
	{
		chdir(oldpwd);
		free(oldpwd);
	}
}

void	add_oldpwd_to_env(t_shell *shell)
{
	if (get_env_var(shell, "OLDPWD") == 0)
		add_env_var(shell, "OLDPWD");
}

void	add_pwd_to_env(t_shell *shell)
{
	if (get_env_var(shell, "PWD") == 0)
		add_env_var(shell, "PWD");
}

//updates the PWD and OLDPWD environment variables
void	update_pwd_n_oldpwd(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	add_oldpwd_to_env(shell);
	oldpwd = get_env_var(shell, "PWD");
	if (!find_var(shell, "PWD"))
		add_pwd_to_env(shell);
	if (oldpwd)
	{
		set_env_var(shell, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (!oldpwd)
		set_env_var(shell, "OLDPWD", 0);
	if (pwd)
	{
		set_env_var(shell, "PWD", pwd);
		free(pwd);
	}
}
