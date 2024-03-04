/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/03/04 11:31:50 by jseidere         ###   ########.fr       */
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

//checks if amount of quotes is even
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

//skips quotes at the end and beginning of a string
char	*skip_quotes(char *str)
{
	size_t	i;
	char	*result;

	i = 0;
	result = NULL;
	if (!quotes_checker(str))
		return (NULL);
	if (str[0] == 34)
	{
		result = malloc(sizeof(char) * (ft_strlen(str) - 1));
		if (!result)
			return (NULL);
		i++;
		if (str[ft_strlen(str) - 1] == '"')
		{
			while (i < ft_strlen(str) - 1)
			{
				result[i - 1] = str[i];
				i++;
			}
		}
	}
	result[i - 1] = '\0';
	return (result);
}

//checks the input and prints the tokens if
void	check_input(char *str)
{
	char	*norm_str;
	t_token	*head;

	if(str[0] == '"')
	{
		str = skip_quotes(str);
		if (!str)
			return ;
	
	}
	norm_str = norm_input(str, token_count(str) + count_chars(str));
	if (!norm_str)
		return ;
	head = assign_token_types(norm_str);
	if (head)
		print_tokens(&head);
}
