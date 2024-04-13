/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:23:44 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/13 07:54:40 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Before char
int	strlen_before_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

//Add environment variable
void	add_env_var(t_shell *shell, char *arg)
{
	t_list	*node;

	node = ft_envnew_l(arg);
	if (!node)
	{
		shell->exitcode = 1;
		return ;
	}
	ft_lstadd_back(&shell->env_list, node);
}

//Export command
void	export_command(t_shell *shell, t_cmd *cmd)
{
	int		len;
	t_list	*tmp;

	if(!cmd->args[1])
	{
		print_export_list(shell->env_list);
		shell->exitcode = 0;
		return ;
	}
	tmp = shell->env_list;
	while (tmp)
	{
		len = strlen_before_char(cmd->args[1], '=');
		if (ft_strncmp(((t_env*)tmp->content)->var, cmd->args[1], len) == 0)
		{
			if(((t_env*)tmp->content)->value && cmd->args[1][len] == '=')
			{
				free(((t_env*)tmp->content)->value);
				((t_env*)tmp->content)->value = ft_strdup(cmd->args[1] + len + 1);
				((t_env*)tmp->content)->flag = 1;
				shell->exitcode = 0;
			}
			return ;
		}
		tmp = tmp->next;
	}
	add_env_var(shell, cmd->args[1]);
	shell->exitcode = 0;
}
