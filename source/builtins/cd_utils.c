/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/14 16:10:12 by jseidere         ###   ########.fr       */
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
			if (((t_env *)tmp->content)->value)
				free(((t_env *)tmp->content)->value);
			((t_env *)tmp->content)->value = ft_strdup(value);
			if (!((t_env *)tmp->content)->value)
				((t_env *)tmp->content)->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

void unset_OLDPWD(t_shell *shell)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = shell->env_list;
	while (curr != NULL)
	{
		if (ft_strncmp(((t_env *)curr->content)->var, "OLDPWD", 6) == 0)
		{
			free_env_var(((t_env *)curr->content));
			if (prev == NULL)
				shell->env_list = curr->next;
			else
				prev->next = curr->next;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

//cd old pwd
void	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_var(shell, "OLDPWD");
	if(chdir(oldpwd) == -1)
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
	if (oldpwd)
		chdir(oldpwd);
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
	if (!is_var(shell, "PWD"))
		add_pwd_to_env(shell);
	if (oldpwd)
		set_env_var(shell, "OLDPWD", oldpwd);
	else if (!oldpwd)
		set_env_var(shell, "OLDPWD", 0);
	if (pwd)
	{
		set_env_var(shell, "PWD", pwd);
		free(pwd);
	}
}
