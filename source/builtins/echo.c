/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:17:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/14 20:06:12 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//print the argument of the echo command
void	print_echo(t_cmd *cmd, int *i, int out)
{
	ft_putstr_fd(cmd->args[*i], out);
	if (cmd->args[*i + 1])
		ft_putstr_fd(" ", out);
}

//Check if -n flag
bool	check_newline(char *str)
{
	int	i;

	i = 1;
	if (!str || !str[0] || str[0] != '-' || str[1] != 'n')
		return (false);
	while (str[i])
	{
		if (str[i] == 'n')
		{
			while (str[i] == 'n' && str[i + 1] == 'n')
				i++;
		}
		else if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

//print the argument of the echo command with out newline
//TODO: still needs to be fixed with more args (?)
void	nnl_echo(t_cmd *cmd, int out)
{
	int	i;
	int	args_len;

	i = 2;
	args_len = count_args(cmd->args);
	if (!cmd->args[i])
		return ;
	while (check_newline(cmd->args[i]) && i < args_len)
	{
		if (cmd->args[i + 1])
			i++;
		else
			return ;
	}
	while (i < args_len)
	{
		print_echo(cmd, &i, out);
		i++;
	}
}

//print the argument of the echo command with newline
void	simple_echo(t_cmd *cmd, int out)
{
	int	i;

	i = 1;
	while (i < count_args(cmd->args))
	{
		print_echo(cmd, &i, out);
		i++;
	}
	ft_putstr_fd("\n", out);
}

//check if the echo command is with or without newline
//and print; if no argument - print newline
void	echo_command(t_shell *shell, t_cmd *cmd, int out)
{
	if (cmd->args[1])
	{
		if (check_newline(cmd->args[1]))
			nnl_echo(cmd, out);
		else
			simple_echo(cmd, out);
	}
	else
		ft_putstr_fd("\n", out);
	shell->exitcode = 0;
}
