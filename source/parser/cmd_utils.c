/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/15 21:35:24 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//adds an argument to the args table
bool	add_args(t_cmd *cmd, char *arg)
{
	int		i;
	char	**res;

	if (!arg || !cmd)
		return (false);
	res = malloc(sizeof(char *) * (count_args(cmd->args) + 2));
	if (!res)
		return (false);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		res[i] = cmd->args[i];
		i++;
	}
	res[i] = ft_strdup(arg);
	if (!res[i])
		return (false);
	res[i + 1] = NULL;
	free(cmd->args);
	cmd->args = res;
	return (true);
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
	if (!shell->paths || !shell->paths[j])
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
		free(command);
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
	if (access(command, F_OK) == 0)
		return (true);
	return (false);
}

bool	find_commands(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->size)
	{
		if (!shell->cmds || !shell->cmds[i].args)
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
