/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:13:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/17 19:03:14 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//counts the number of characters in a string
int	count_chars(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (shell->input[i])
	{
		while ((shell->input[i] == ' ' || shell->input[i] == '\t'))
			i++;
		if (shell->input[i] != ' ' || shell->input[i] != '\t')
			count++;
		if (shell->input[i] && is_quote(shell->input[i]))
		{
			count++;
			i++;
			while (!is_quote(shell->input[i]))
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
	result[(*i)] = str[*j];
	(*i)++;
	(*j)++;
	while (str[*j] != '\0' && !is_quote(str[*j]))
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
	if (str[*j] == ' ')
	{
		while (str[*j] == ' ' && str[*j + 1] == ' ')
			(*j)++;
	}
	if (((*j > 0 && (is_sep(str[*j]) && !is_sep(str[*j - 1]))))
		&& str[*j - 1] != ' ' && str[*j] != '\0')
	{
		result[(*i)] = ' ';
		(*i)++;
	}
	result[*i] = str[*j];
	(*i)++;
	(*j)++;
	if ((*j > 0 && (!is_sep(str[*j]) && is_sep(str[*j - 1])))
		&& str[*j] != ' ' && str[*j] != '\0')
	{
		result[(*i)] = ' ';
		(*i)++;
	}
}

//get input and return a normed input
//TODO: delete printf
void	norm_input(t_shell *shell)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = token_count(shell) - 1 + count_chars(shell);
	if (!quotes_checker(shell->input))
		return ;
	shell->norm_input = malloc(sizeof(char) * (len + 1));
	if (!shell->norm_input)
		return ;
	while (i < len)
		process_character(shell->input, shell->norm_input, &i, &j);
	shell->norm_input[i] = '\0';
	printf("Normed input: %s\n", shell->norm_input);
}
