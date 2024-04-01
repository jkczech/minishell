/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:23:11 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/01 18:16:56 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* //open infile and outfile, show errors respectively
void	open_files(t_shell *shell)
{
	shell->infile = open(shell->argv[1], O_RDONLY);
	if (shell->infile == -1)
	{
		if (access(shell->argv[1], F_OK) != 0)
			error_msg(shell->argv[1]);
		else if (access(shell->argv[1], R_OK) != 0)
			error_msg(shell->argv[1]);
		else
			ft_putstr_fd(ERR_IN, 2);
	}
	shell->outfile = open(shell->argv[shell->size + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->outfile == -1)
	{
		if (access(shell->argv[shell->size + 2], W_OK) != 0)
			error_msg(shell->argv[shell->size + 2]);
		else
			ft_putstr_fd(ERR_OUT, 2);
	}
}

//read all the commands, infile, outfile, open fds for files
//return value: if any error false at first error, else true
bool	parse_input(t_shell *shell)
{
	int	i;

	find_paths(shell); //deleted function
	// if (shell->heredoc)
	// 	open_here_doc(shell);
	// else
	// 	open_files(shell);
	i = 0;
	while (i < shell->size)
	{
		//shell->cmds[i].found = false;
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
