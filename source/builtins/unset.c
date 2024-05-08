/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/21 16:00:45 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_var(t_env *env)
{
	free(env->var);
	free(env->value);
	free(env);
}

//find env var
t_env	*find_env_var(t_shell *shell, char *var)
{
	t_list	*tmp;
	int		len;

	tmp = shell->env_list;
	len = strlen_before_char(var, '=');
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->var, var, len) == 0)
			return ((t_env *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

//delete env var
void delete_env_var(t_shell *shell, char *var)
{
	t_list	*prev;
	t_list	*curr;
	int		len;

	prev = NULL;
	curr = shell->env_list;
	len = strlen_before_char(var, '=');
	while (curr)
	{
		if (ft_strncmp(((t_env *)curr->content)->var, var, len) == 0)
		{
			if (prev == NULL)
				shell->env_list = curr->next;
			else
				prev->next = curr->next;
			free_env_var(((t_env *)curr->content));
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

// Unset command
void	unset_command(t_shell *shell, t_cmd *cmd)
{
	int			len;
	t_list		*prev;
	t_list		*curr;

	prev = NULL;
	curr = shell->env_list;
	while (curr != NULL)
	{
		len = strlen_before_char(cmd->args[1], '=');
		if (ft_strncmp(((t_env *)curr->content)->var, cmd->args[1], len) == 0)
		{
			if (prev == NULL)
				shell->env_list = curr->next;
			else
				prev->next = curr->next;
			free_env_var(((t_env *)curr->content));
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	shell->exitcode = 0;
}
	// Variable not found
	// Add logic to handle the case where the variable isn't found
	// variable still in export list with last command 
	// handle PWD and OLDPWD if PWD is unset
