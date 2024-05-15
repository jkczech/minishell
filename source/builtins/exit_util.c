/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:46:33 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/15 15:13:17 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Checks amount of arguments
bool	check_amount_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (false);
	return (true);
}

//Check if argument is numeric
bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		if (i == 0 && str[i] == '+')
			i++;
		if (str[i] == '0')
		{
			while (str[i] == '0' && str[i + 1] == '0')
				i++;
		}
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

// Handle overflow and underflow
long	convert_exit_status(t_cmd *cmd)
{
	long	exit_status;

	exit_status = 0;
	if (cmd->args[1][0] == '-')
	{
		exit_status = ft_atol(cmd->args[1]);
		if (exit_status < 0)
			exit_status = 256 + exit_status;
	}
	else if (is_numeric(cmd->args[1]))
	{
		exit_status = ft_atol(cmd->args[1]);
		if (exit_status > 255)
			exit_status = exit_status % 256;
	}
	return (exit_status);
}

// checks if argument is bigger than MAX_LONG_INT
bool	check_overflow(char *str)
{
	long	input;
	char	*input_str;

	if (*str == '+')
		str++;
	if (*str == '0')
	{
		while (*str == '0')
			str++;
	}
	if (ft_strlen(str) > 20)
		return (false);
	input = ft_atol(str);
	input_str = ft_ltoa(input);
	if (!input_str)
		return (false);
	if (ft_strncmp(input_str, str, ft_strlen(str)) == 0)
	{
		free(input_str);
		return (true);
	}
	free(input_str);
	return (false);
}
