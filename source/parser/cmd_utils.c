/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/10 15:18:22 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//adds an argument to the args table
void	add_args(t_cmd *cmd, char *arg)
{
	int		i;
	char	**res;

	if (cmd->args == NULL)
	{
		cmd->args = (char **)malloc(sizeof(char *) * 2);
		cmd->args[0] = ft_strdup(arg);
		cmd->args[1] = NULL;
		return ;
	}
	res = malloc(sizeof(char *) * (count_args(cmd->args) + 2));
	if (!res)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		res[i] = cmd->args[i];
		i++;
	}
	res[i++] = ft_strdup(arg);
	res[i] = NULL;
	free(cmd->args);
	cmd->args = res;
}

//search for command in shell.cmd[i], and search for path
bool	find_command(t_shell *shell, int i)
{
	char	*command;
	int		j;

	if (shell->cmds[i].args[0]
		&& is_command(shell->cmds[i].args[0]))
		return (save_command(shell, i, shell->cmds[i].args[0]));
	j = 0;
	if (!shell->paths)
		return (cmd_not_found(shell, i));
	while (shell->paths && shell->paths[j])
	{
		command = ft_strjoin3(shell->paths[j],
				"/", shell->cmds[i].args[0]);
		if (is_command(command))
		{
			shell->cmds[i].path = command;
			break ;
		}
		j++;
		if (!shell->paths[j])
			cmd_not_found(shell, i);
	}
	return (shell->cmds[i].path != NULL);
}

bool	save_command(t_shell *shell, int i, char *command)
{
	if (!command)
		return (false);
	shell->cmds[i].path = ft_strdup(command);
	return (shell->cmds[i].path != NULL);
}

//check if command is valid
bool	is_command(char *command)
{
	if (!command)
		return (false);
	if (access(command, F_OK) == 0 && ft_strncmp(command, "/", 1) == 0)
		return (true);
	return (false);
}

bool	find_commands(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size)
	{
		if (!shell->cmds[i].args)
			return (false);
		if (is_builtin(shell, i))
		{
			i++;
			continue ;
		}
		find_command(shell, i);
		i++;
	}
	return (true);
}
