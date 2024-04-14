/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/14 10:56:25 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_env_var(t_env *env) {
  free(env->var);
  free(env->value);
  free(env);
}


void unset_command(t_shell *shell, t_cmd *cmd) {
  int len;
  t_list *prev = NULL;
  t_list *curr = shell->env_list;

  while (curr != NULL)
  {
    len = strlen_before_char(cmd->args[1], '=');
    if (ft_strncmp(((t_env*)curr->content)->var, cmd->args[1], len) == 0)
	{
      if (prev == NULL)
        shell->env_list = curr->next;
	  else
        prev->next = curr->next;
      free_env_var(((t_env*)curr->content));
      return;
    }
    prev = curr;
    curr = curr->next;
  }

  // Variable not found
  // (Optional) Add logic to handle the case where the variable isn't found
  // For example, print an error message

  shell->exitcode = 0;
}

/* void	unset_command(t_shell *shell, t_cmd *cmd)
{
	int		len;
	t_list	*tmp;

	tmp = shell->env_list;
	while (tmp)
	{
		len = strlen_before_char(cmd->args[1], '=');
		if (ft_strncmp(((t_env*)tmp->content)->var, cmd->args[1], len) == 0)
		{
				free(((t_env*)tmp->content)->value);
                free(((t_env*)tmp->content)->var);
                free((t_env*)tmp->content);
			return ;
		}
		tmp = tmp->next;
	}
	//add_env_var(shell, cmd->args[1]);
	shell->exitcode = 0;
} */

// warum env in export list nach unset?
//bzw letzter Command wird in export list gespeichert


