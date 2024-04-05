/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/05 16:15:32 by jseidere         ###   ########.fr       */
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
	printf("ARG: %s\n", arg);
	res = malloc(sizeof(char *) * (count_args(cmd->args) + 2));
	if (!res)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		res[i] = cmd->args[i];
		i++;
	}
	printf("I: %d\n", i);
	printf("ARG: %s\n", arg);
	res[i++] = ft_strdup(arg);
	res[i] = NULL;
	free(cmd->args);
	cmd->args = res;
}

//counts the number of arguments for the args table
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
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
