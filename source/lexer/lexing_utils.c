/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:11:09 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/09 18:13:55 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

//additionnal function for token_count
void	token_count_util(char *str, int *i, int *count)
{
	if (str[*i] != '\0' && !is_sep(str[*i]))
	{
		(*count)++;
		if (is_quote(str[*i]))
			while (!is_quote(str[++(*i)]))
				;
		while (str[*i] != ' ' && str[*i] != '\t'
			&& str[*i] != '\0' && !is_sep(str[*i]))
			(*i)++;
	}
	if (double_sep(str, *i))
		(*i)++;
	if (is_sep(str[*i]))
	{
		(*i)++;
		(*count)++;
	}
}