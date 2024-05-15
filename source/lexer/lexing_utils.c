/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:11:09 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/15 19:10:54 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//additionnal function for token_count
void	token_count_util(char *str, int *i, int *count)
{
	if (str[*i] != '\0' && !is_sep(str[*i]))
	{
		(*count)++;
		if (is_quote(str[*i]))
			while (str[*i] && !is_quote(str[++(*i)]))
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

//counts the number of tokens in a string
int	token_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		token_count_util(str, &i, &count);
	}
	return (count);
}

//convert whitespace to space
void	convert_whitespace(char *str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote.type = 0;
	quote.in_quotes = false;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]) && !quote.in_quotes)
		{
			quote.type = str[i];
			quote.in_quotes = true;
			i++;
		}
		if (str[i] && ft_isspace(str[i]) && !quote.in_quotes)
			str[i] = ' ';
		if (str[i] && quote.in_quotes && str[i] == quote.type)
		{
			quote.in_quotes = false;
			quote.type = 0;
		}
		i++;
	}
}
