/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:13:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 20:39:23 by jkoupy           ###   ########.fr       */
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
		while (str[i + 1] && (str[i] == ' ' || str[i] == '\t'))
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
	if (str[*j] == '\0')
		return ;
	result[(*i)] = str[*j];
	(*i)++;
	(*j)++;
}

//void process_char (t_shell *shell,)

//processes a character
void	process_character(char *s, char *result, int *i, int *j)
{
	if (s[*j] && is_quote(s[*j]))
		process_char_quotes(s, result, i, j);
	if (s[*j] && (s[*j] == ' ' || s[*j] == '\t'))
	{
		while (s[*j] && ((s[*j] == ' ' && s[*j + 1] == ' ')
				|| (s[*j] == '\t')))
		{
			if (s[(*j)++] == '\t')
				result[(*i)++] = ' ';
		}
	}
	if (*j == 0 && (is_sep(s[*j]) && is_sep(s[*j + 1])) && !double_sep(s, *j))
	{
		result[(*i)++] = s[(*j)++];
		result[(*i)++] = ' ';
	}
	if (((*j > 0 && s[*j - 1] != '\0' && s[*j] != '\0'
				&& (is_sep(s[*j]) && !is_sep(s[*j - 1])))
			&& s[*j - 1] != ' ') || (*j == 0 && is_sep(s[*j]) && !is_sep(s[0])))
		result[(*i)++] = ' ';
	if (s[*j] != '\0')
		result[(*i)++] = s[(*j)++];
	if ((*j > 0 && s[*j - 1] != '\0' && s[*j] != '\0'
			&& (!is_sep(s[*j]) && is_sep(s[*j - 1]))) && s[*j] != ' ')
		result[(*i)++] = ' ';
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
	while (i < len && shell->input[j])
		process_character(shell->input, shell->norm_input, &i, &j);
	shell->norm_input[i] = '\0';
}
