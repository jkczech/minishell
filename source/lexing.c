/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:13:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/01 15:55:41 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

//counts the number of tokens in a string
int	token_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		/* if(str[i] == '"')
		{
			printf("Str[i]: %c\n", str[i]);
			while (str[i] != '"' && str[i] != '\0')
				i++;
			i++;
			count++;
		} */
		if (str[i] != '\0' && !is_sep(str[i]))
		{
			count++;
			while (str[i] != ' ' && str[i] != '\t'
				&& str[i] != '\0' && !is_sep(str[i]))
				i++;
		}
		if (double_sep(str, i))
			i++;
		if (is_sep(str[i]))
		{
			i++;
			count++;
		}
	}
	printf("Token_count: %d\n", count);
	return (count);
}

//counts the number of characters in a string
int	count_chars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		if (str[i] != ' ' || str[i] != '\t')
		{
			count++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		i++;
	}
	printf("Char_count: %d\n", count);
	return (count);
}
//bool qotations_checker(char *str)

//processes a character
void	process_character(char *str, char *result, int *i, int *j)
{
	if (((*j > 0 && (is_sep(str[*j]) && !is_sep(str[*j - 1])))
			|| str[*j] == '-') && str[*j - 1] != ' ')
	{
		result[(*i)] = ' ';
		(*i)++;
	}
	result[*i] = str[*j];
	(*i)++;
	(*j)++;
	if ((*j > 0 && (!is_sep(str[*j]) && is_sep(str[*j - 1])))
		&& str[*j] != ' ')
	{
		result[(*i)] = ' ';
		(*i)++;
	}
}

//get input and return a normed input
char	*norm_input(char *str, int len)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (!quotes_checker(str))
		return (NULL);
	while (i < len)
	{
		process_character(str, result, &i, &j);
	}
	result[i] = '\0';
	printf("Normed input: %s\n", result);
	return (result);
}
