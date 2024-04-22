/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:23:44 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/22 18:25:26 by jseidere         ###   ########.fr       */
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

//TODO: delete print
bool	simple_export(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		print_export_list(shell->env_list);
		shell->exitcode = 0;
		return (true);
	}
	return (false);
}

//Export command
void	export_command(t_shell *shell, t_cmd *cmd)
{
	int		len;
	t_list	*tmp;
	int		i;
	bool	swap;

	i = 1;
	if (simple_export(shell, cmd))
		return ;
	while(cmd->args[i])
	{
		swap = false;
		tmp = shell->env_list;
		if (is_valid_var(cmd->args[i]) == false)
		{
			shell->exitcode = 1;
			ft_putstr_fd("MiNiSHell: export: `command\': not a valid identifier\n", 2);
			i++;
			continue;
		}
		while (tmp)
		{
			len = strlen_before_char(((t_env *)tmp->content)->var, '=');
			if (ft_strncmp(((t_env *)tmp->content)->var, cmd->args[i], len) == 0)
			{
				if (((t_env *)tmp->content)->value && cmd->args[i][len] == '=')
				{
					free(((t_env *)tmp->content)->value);
					((t_env *)tmp->content)->value = \
					ft_strdup (cmd->args[i] + len + 1);
					((t_env *)tmp->content)->flag = 1;
					shell->exitcode = 0;
					swap = true;
				}
			}
			tmp = tmp->next;
		}
		if(!swap)
			add_env_var(shell, cmd->args[i]);
		i++;
	}
	shell->exitcode = 0;
}
