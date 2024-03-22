/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:17:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/21 16:29:22 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Prints the argument of the echo command
void	print_echo(t_shell *shell, t_cmd *cmd, int *i)
{
	if (ft_strncmp(cmd->args[*i], "$?", 2) == 0)
	{
		ft_putstr_fd(ft_itoa(shell->exitcode), 1);
		if (cmd->args[*i + 1])
			ft_putstr_fd(" ", 1);
		(*i)++;
		return ;
	}
	ft_putstr_fd(cmd->args[*i], 1);
	if (cmd->args[*i + 1])
		ft_putstr_fd(" ", 1);
}

//Prints the argument of the echo command with out newline
//Still needs to be fixed with more args
void	print_nnl_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	args_len;

	i = 2;
	args_len = args_counter(cmd->args);
	if (!cmd->args[i])
		return ;
	while (ft_strncmp(cmd->args[i], "-n", 2) == 0 && i < args_len)
	{
		if (cmd->args[i + 1])
			i++;
		else
			return ;
	}
	while(i < args_len)
	{
		print_echo(shell, cmd, &i);
		i++;
	}
}

//Prints the argument of the echo command with newline
void	simple_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < args_counter(cmd->args))
	{
		print_echo(shell, cmd, &i);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

//Checks if the command is echo and executes it
void	echo_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[1])
	{
		if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
			print_nnl_echo(shell, cmd);
		else
			simple_echo(shell, cmd);
	}
}
