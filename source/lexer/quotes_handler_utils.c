/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:28:55 by jakob             #+#    #+#             */
/*   Updated: 2024/04/17 19:00:58 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a character is a quote
bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

//initializes variables
void	init_variables(int *i, int *len, char *q, bool *q_closed)
{
	*i = 0;
	*len = 0;
	*q = '\0';
	*q_closed = true;
}

//determines the quote
void	determine_quote(char *str, int *i, char *q, bool *q_closed)
{
	if (*q_closed && is_quote(str[*i]))
	{
		*q_closed = false;
		*q = str[*i];
		(*i)++;
	}
}

//refreshes the quote
void	refresh_quote(char *str, int *i, char *q, bool *q_closed)
{
	if (str[*i] == *q && !*q_closed)
	{
		*q_closed = true;
		(*i)++;
	}
}
