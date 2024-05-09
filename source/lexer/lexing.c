/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:13:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/09 16:10:26 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//counts the number of characters in a string
int	count_chars(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] != ' ' || str[i] != '\t')
			count++;
		if (str[i] && is_quote(str[i]))
		{
			quote = str[i++];
			count++;
			while (str[i] != quote && str[i])
			{
				count++;
				i++;
			}
		}
		i++;
	}
	return (count);
}

//processes char in quotes
void	process_char_quotes(char *str, char *result, int *i, int *j)
{
	t_quote	quote;

	quote.type = str[*j];
	result[(*i)] = str[*j];
	(*i)++;
	(*j)++;
	while (str[*j] != '\0' && quote.type != str[*j])
	{
		result[(*i)] = str[*j];
		(*i)++;
		(*j)++;
	}
	result[(*i)] = str[*j];
	(*i)++;
	(*j)++;
}

//processes a character
void	process_character(char *str, char *result, int *i, int *j)
{
	if (is_quote(str[*j]))
		process_char_quotes(str, result, i, j);
	if (str[*j] != '\0' && str[*j] == ' ')
	{
		while (str[*j] && str[*j] == ' ' && str[*j + 1] == ' ')
			(*j)++;
	}
	if (((*j > 0 && str[*j - 1] != '\0' && str[*j] != '\0'
				&& (is_sep(str[*j]) && !is_sep(str[*j - 1]))))
		&& str[*j - 1] != ' ')
	{
		result[(*i)] = ' ';
		(*i)++;
	}
	result[*i] = str[*j];
	(*i)++;
	(*j)++;
	if ((*j > 0 && str[*j - 1] != '\0' && str[*j] != '\0'
			&& (!is_sep(str[*j]) && is_sep(str[*j - 1])))
		&& str[*j] != ' ')
	{
		result[(*i)] = ' ';
		(*i)++;
	}
}

//get input and return a normed input
void	norm_input(t_shell *shell)
{
	int		i;
	int		j;
	int		len;

	if (!shell->input)
		return ;
	len = token_count(shell->input) - 1 + count_chars(shell->input) + 1;
	if (!quotes_checker(shell->input))
		return ;
	shell->norm_input = malloc(sizeof(char) * (len + 1));
	if (!shell->norm_input)
		return ;
	i = 0;
	j = 0;
	while (i < len)
		process_character(shell->input, shell->norm_input, &i, &j);
	shell->norm_input[i] = '\0';
}
