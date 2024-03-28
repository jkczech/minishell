/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/28 11:53:55 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//adds an argument to the args table
void	add_args(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**res;
	char	**new_args;

	if (cmd->args == NULL)
	{
		cmd->args = ft_split(arg, ' ');
		return ;
	}
	new_args = ft_split(arg, ' ');
	res = malloc(sizeof(char *) * (count_args(cmd->args, new_args) + 1));
	if (!res)
		return ;
	i = -1;
	while (cmd->args[++i])
		res[i] = cmd->args[i];
	j = 0;
	while (new_args[j])
		res[i++] = new_args[j++];
	res[i] = NULL;
	free(new_args);
	free(cmd->args);
	cmd->args = res;
}

//counts the number of arguments for the args table
int	count_args(char **args, char **new_args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
		i++;
	j = 0;
	while (new_args[j])
		j++;
	return (i + j);
}

//check if command is valid, if so, save it into shell
bool	is_command(t_shell *shell, char *command, int i)
{
	if (!command)
		return (false);
	if (access(command, F_OK) == 0 && ft_strncmp(command, "/", 1) == 0)
	{
		shell->cmds[i].path = ft_strdup(command);
		if (!shell->cmds[i].path)
			return (false);
		free(command);
		shell->cmds[i].found = true;
		return (true);
	}
	free(command);
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
		if (!(shell->cmds[i].input == -1) && \
			!(shell->cmds[i].output == -1))
		{
			if (is_builtin(shell, i))
			{
				i++;
				continue ;
			}
			find_command(shell, i);
		}
		i++;
	}
	return (true);
}

//search for command in shell.cmd[i], and search for path
void	find_command(t_shell *shell, int i)
{
	char	*command;
	int		j;

	if (shell->cmds[i].args[0]
		&& is_command(shell, ft_strdup(shell->cmds[i].args[0]), i))
		return ;
	j = 0;
	if (!shell->paths)
		return (cmd_not_found(shell, i));
	while (shell->paths && shell->paths[j])
	{
		command = ft_strjoin3(shell->paths[j],
				"/", shell->cmds[i].args[0]);
		if (is_command(shell, command, i))
			break ;
		j++;
		if (!shell->paths[j])
			cmd_not_found(shell, i);
	}
}
