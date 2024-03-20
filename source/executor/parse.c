/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:23:11 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/20 11:34:14 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int i;

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
	while (shell->paths[j])
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

//find PATH in environment variables and save it into shell->paths
void	find_paths(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp)
		return ;
	while (shell->envp[i] && ft_strncmp(shell->envp[i], "PATH", 4) != 0)
		i++;
	if (shell->envp[i] && ft_strncmp(shell->envp[i], "PATH", 4) == 0)
		shell->paths = ft_split(shell->envp[i] + 5, ':');
}

/* //open infile and outfile, show errors respectively
void	open_files(t_shell *shell)
{
	shell->infile = open(shell->argv[1], O_RDONLY);
	if (shell->infile == -1)
	{
		if (access(shell->argv[1], F_OK) != 0)
			error_message(shell->argv[1]);
		else if (access(shell->argv[1], R_OK) != 0)
			error_message(shell->argv[1]);
		else
			ft_putstr_fd(ERR_IN, 2);
	}
	shell->outfile = open(shell->argv[shell->size + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->outfile == -1)
	{
		if (access(shell->argv[shell->size + 2], W_OK) != 0)
			error_message(shell->argv[shell->size + 2]);
		else
			ft_putstr_fd(ERR_OUT, 2);
	}
}

//read all the commands, infile, outfile, open fds for files
//return value: if any error false at first error, else true
bool	parse_input(t_shell *shell)
{
	int	i;

	find_paths(shell);
	// if (shell->heredoc)
	// 	open_here_doc(shell);
	// else
	// 	open_files(shell);
	i = 0;
	while (i < shell->size)
	{
		shell->cmds[i].found = false;
		//shell->cmds[i].args = \
			//ft_split(shell->argv[i + 2 + shell->heredoc], ' ');
		if (!shell->cmds[i].args)
			return (false);
		if (!(i == 0 && shell->infile == -1)
			&& !(i == shell->size - 1 && shell->outfile == -1))
			find_command(shell, i);
		i++;
	}
	return (true);
} */
