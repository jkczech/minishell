/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:23:44 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/15 21:34:17 by jseidere         ###   ########.fr       */
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

bool	simple_export(t_shell *shell, t_cmd *cmd, int out)
{
	if (!cmd->args[1])
	{
		print_export_list(shell->env_list, out);
		shell->exitcode = 0;
		return (true);
	}
	return (false);
}

//export command
void	export_command(t_shell *shell, t_cmd *cmd, int out)
{
	int		i;
	bool	swap;

	i = 1;
	if (simple_export(shell, cmd, out))
		return ;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '-')
		{
			export_error_minus(shell, cmd->args[i++]);
			continue ;
		}
		if (!is_valid_var(cmd->args[i]))
		{
			export_error(shell, cmd->args[i++]);
			continue ;
		}
		export_loop(shell, cmd, &i, &swap);
		if (!swap)
			add_env_var(shell, cmd->args[i]);
		i++;
	}
	free_array(shell->envp);
	shell->envp = envp_list_into_char(shell->env_list);
}

//export loop
void	export_loop(t_shell *shell, t_cmd *cmd, int *i, bool *swap)
{
	t_list	*tmp;
	int		len;

	*swap = false;
	tmp = shell->env_list;
	while (tmp)
	{
		len = strlen_before_char(((t_env *)tmp->content)->var, '=');
		if (ft_strncmp(((t_env *)tmp->content)->var, cmd->args[*i], len) == 0)
		{
			if (((t_env *)tmp->content)->value && cmd->args[*i][len] == '=')
			{
				free(((t_env *)tmp->content)->value);
				((t_env *)tmp->content)->value = \
				ft_strdup (cmd->args[*i] + len + 1);
				((t_env *)tmp->content)->flag = 1;
				shell->exitcode = 0;
				*swap = true;
			}
		}
		tmp = tmp->next;
	}
}
