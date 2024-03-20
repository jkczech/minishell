/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:17:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/20 13:46:15 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_echo (t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "$?", 2) == 0)
		{
			ft_putstr_fd(ft_itoa(shell->exitcode), 1);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
			continue;
		}
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

//Prints the argument of the echo command with out newline
void print_nnl_echo(t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 2;
	if(!cmd->args[i])
		return ;
	while (ft_strncmp(cmd->args[i], "-n", 2) == 0)
		i++;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "$?", 2) == 0)
		{
			ft_putstr_fd(ft_itoa(shell->exitcode), 1);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
			continue;
		}
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

//Prints the argument of the echo command
void simple_echo(t_shell *shell, t_cmd *cmd)
{
	print_echo(shell, cmd);
	ft_putstr_fd("\n", 1);
}

void	echo_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd && ft_strncmp(cmd->args[0], "echo", 4) == 0)
	{
		if (cmd->args[1])
		{
			if(ft_strncmp(cmd->args[1], "-n", 2) == 0)
				print_nnl_echo(shell, cmd);
			else
				simple_echo(shell, cmd);
		}
	}
}
