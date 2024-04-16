/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/04/16 03:21:14 by jkoupy           ###   ########.fr       */
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

//deletes quotes at the beginning and the end of a str
void	del_quotes(char **str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(*str);
	tmp = (char *)malloc(sizeof(char) * (len - 1));
	if (!tmp)
		return ;
	while ((*str)[i + 1])
	{
		tmp[i] = (*str)[i + 1];
		i++;
	}
	tmp[i - 1] = '\0';
	free(*str);
	*str = tmp;
}

//checks the input and saves it in a list of tokens
//if the input is invalid, returns false
bool	check_input(t_shell *shell)
{
	norm_input(shell);
	if (!shell->norm_input)
		return (false);
	if (!check_parse_errors(shell))
		return (false);
	return (true);
}


