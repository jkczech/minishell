/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/02/27 16:15:18 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//checks if a character is a separator
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

char	*skip_quotes(char *str)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!quotes_checker(str))
		return (NULL);
	if (str[0] == '"')
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

void	check_input(char *str)
{
	char	*norm_str;
	t_token	*head;

	str = skip_quotes(str);
	if (!str)
		return ;
	norm_str = norm_input(str, token_count(str) + count_chars(str));
	if (!norm_str)
		return ;
	head = assign_token_types(norm_str);
	if (head)
		print_tokens(&head);
}
