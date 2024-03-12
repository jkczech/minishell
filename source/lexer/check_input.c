/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/03/11 13:14:16 by jkoupy           ###   ########.fr       */
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
		result[i - 1] = '\0';
	}
	return (result);
}

//checks the input and saves it in a list of tokens
//if the input is invalid, returns false
bool	check_input(t_shell *shell)
{
	t_token	*head;

	if (shell->input[0] == '"')
	{
		shell->input = skip_quotes(shell->input);
		if (!shell->input)
			return (false);
	}
	norm_input(shell, token_count(shell) - 1 + count_chars(shell));
	if (!shell->norm_input)
		return (false);
	head = assign_token_types(shell);
	shell->tokens = &head;
	if (shell->tokens)
		print_tokens(shell->tokens);
	return (true);
}
