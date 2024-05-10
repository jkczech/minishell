/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/05/10 16:21:04 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a character is a separator
bool	is_sep(char c)
{
	int	i;

	i = 0;
	while (SEPARATOR[i])
	{
		if (SEPARATOR[i] == c)
			return (true);
		else
			i++;
	}
	return (false);
}

//checks if a character is a double separator
bool	double_sep(char *str, int i)
{
	if ((str[i] == '|' && str[i + 1] == '|')
		|| (str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		return (true);
	return (false);
}

//check if pipe is last character
bool	check_pipe_last(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			j = i + 1;
			while (str[j] == ' ')
				j++;
			if (str[j] == '\0')
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

//checks the input and saves it in a list of tokens
//if the input is invalid, returns false
bool	check_input(t_shell *shell)
{
	if (!shell->input || !*shell->input)
		return (false);
	if (!quotes_checker(shell->input) || check_pipe_last(shell->input))
	{
		ft_putstr_fd("MiNiSHell: syntax error\n", 2);
		shell->exitcode = 2;
		return (false);
	}
	norm_input(shell);
	if (!shell->norm_input)
		return (false);
	if (!check_parse_errors(shell))
		return (false);
	return (true);
}
