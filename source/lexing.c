/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:13:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/26 18:12:25 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_sep(char c)
{
	int	i;

	i = 0;
	while (OPERATOR[i])
	{
		if (OPERATOR[i] == c)
			return (true);
		else
			i++;
	}
	return (false);
}

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
		if (str[i] != '\0' && !is_sep(str[i]))
		{
			count++;
			while (str[i] != ' ' && str[i] != '\t'
				&& str[i] != '\0' && !is_sep(str[i]))
				i++;
		}
		if ((str[i] == '|' && str[i + 1] == '|')
			|| (str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
			i++;
		if (is_sep(str[i++]))
			count++;
	}
	return (count);
}

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
	return (count);
}

bool	quotes_checker(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		return (false);
	return (true);
}

void handle_quotes(char *str)
{
	if(quotes_checker(str))
		printf("Quotes are balanced\n");
	else
	{
		printf("Quotes are not balanced\n");
		return ;
	}
}


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
	if(!quotes_checker(str))
		return (NULL);
	while (i < len)
	{
		if (str[j] == ' ' && str[j + 1] == ' ')
		{
			while (str[j] == ' ' && str[j + 1] == ' ')
				j++;
		}
		if (((j > 0 && (is_sep(str[j]) && !is_sep(str[j - 1])))
				|| str[j] == '-') && str[j - 1] != ' ')
			result[i++] = ' ';
		result[i++] = str[j++];
		if ((j > 0 && j < i) && (!is_sep(str[j])
				&& is_sep(str[j - 1])) && str[j] != ' ')
			result[i++] = ' ';
	}
	result[i] = '\0';
	printf("Normed input: %s\n", result);
	return (result);
}

/* head = split_and_store(norm_str, " ");
	if(head)
	print_tokens(&head); */

void	check_input(char *str)
{
	char	*norm_str;
	t_token	*head;

	norm_str = norm_input(str, token_count(str) + count_chars(str));
	if (!norm_str)
		return ;
	head = assign_token_types(norm_str);
	if (head)
		print_tokens(&head);
}
