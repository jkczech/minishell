/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/17 12:24:59 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_var(t_env *env)
{
	free(env->var);
	free(env->value);
	free(env);
}

void	unset_command(t_shell *shell, t_cmd *cmd)
{
	int			len;
	t_list	*prev;
	t_list	*curr;

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
