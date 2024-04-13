/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/13 08:39:37 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	unset_command(t_shell *shell, t_cmd *cmd)
{
	int		len;
	t_list	*tmp;

	tmp = shell->env_list;
	while (tmp)
	{
		len = strlen_before_char(cmd->args[1], '=');
		if (ft_strncmp(((t_env*)tmp->content)->var, cmd->args[1], len) == 0)
		{
			if(((t_env*)tmp->content)->value)
			{
				free(((t_env*)tmp->content)->value);
                free(((t_env*)tmp->content)->var);
                free((t_env*)tmp->content);    
			}
			return ;
		}
		tmp = tmp->next;
	}
	//add_env_var(shell, cmd->args[1]);
	shell->exitcode = 0;
}

// warum env in export list nach unset?
//bzw letzter Command wird in export list gespeichert


