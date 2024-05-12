/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:00:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/12 22:50:23 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a character is a delimiter
int	is_delimiter(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//returns the length of a token
int	token_len(char *str, int i, const char *delim)
{
	t_quote	quote;
	int		len;

	quote.in_quotes = true;
	quote.type = 0;
	len = 0;
	while (str[i] && (!is_delimiter(str[i], delim) || !quote.in_quotes))
	{
		if (is_quote(str[i]) && quote.in_quotes)
		{
			quote.type = str[i];
			quote.in_quotes = false;
		}
		else if (str[i] == quote.type && !quote.in_quotes)
		{
			quote.in_quotes = true;
			quote.type = 0;
		}
		len++;
		i++;
	}
	len++;
	return (len);
}

//skips spaces in a string
void	skip_spaces(char *str, int *index)
{
	while (str[*index] && str[*index] == ' ')
		(*index)++;
}

//returns the type of a token
int	what_token(char *str, int index)
{
	if (str[index] == '<' && str[index + 1] == '<')
		return (HEREDOC);
	else if (str[index] == '>' && str[index + 1] == '>')
		return (APPEND);
	else if (str[index] == '<')
		return (INPUT);
	else if (str[index] == '>')
		return (OUTPUT);
	else if (str[index] == '|')
		return (PIPE);
	else
		return (WORD);
}

//process_pipe_token
void	add_null_pipe(t_token **head, t_token *token, char *content)
{
	free(content);
	content = NULL;
	token = create_token(NULL, PIPE);
	add_token(head, token);
}
