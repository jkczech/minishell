/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/12 15:55:21 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_var(t_env *env)
{
	free(env->var);
	free(env->value);
	free(env);
}

//delete env var
void	delete_env_var(t_shell *shell, char *var)
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

// Unset command
void	unset(t_shell *shell, char *args)
{
	int			len;
	t_list		*prev;
	t_list		*curr;

	prev = NULL;
	curr = shell->env_list;
	/* if (cmd->args[1] == NULL)
		return ; */
	while (curr != NULL)
	{
		len = strlen_before_char(args, '=');
		if (ft_strncmp(((t_env *)curr->content)->var, args, len) == 0)
		{
			delete_env_var(shell, args);
			if (prev == NULL)
				shell->env_list = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	shell->exitcode = 0;
}

void   unset_command(t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->args[i])
	{
		unset(shell, cmd->args[i]);
		i++;
	}
}

	// Variable not found
	// Add logic to handle the case where the variable isn't found
	// variable still in export list with last command 
	// handle PWD and OLDPWD if PWD is unset
