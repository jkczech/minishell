/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/08 17:07:05 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//Unset command
void	unset_command(t_shell *shell, t_cmd *cmd)
{
    int		i;
    int		len;
    t_list	*tmp;

    i = 1;
    if (!cmd->args[i])
    {
        shell->exitcode = 0;
        return ;
    }
    len = strlen_before_char(cmd->args[1], '=');
    tmp = shell->env_list;
    while (tmp)
    {
        if (ft_strncmp(tmp->content, cmd->args[1], len) == 0)
        {
            free(tmp->content);
            tmp->content = NULL;
            shell->exitcode = 0;
            return ;
        }
        tmp = tmp->next;
    }
    shell->exitcode = 0;
}
