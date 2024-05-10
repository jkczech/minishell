/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:00:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/09 18:55:07 by jseidere         ###   ########.fr       */
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
	
	quote.q_closed = true;
	quote.type = 0;
	len = 0;
	while (str[i] && (!is_delimiter(str[i], delim) || !quote.q_closed))
	{
		if (is_quote(str[i]) && quote.q_closed)
		{
			quote.type = str[i];
			quote.q_closed = false;
		}
		else if (str[i] == quote.type && !quote.q_closed)
		{
			quote.q_closed = true;
			quote.type = 0;
		}
		len++;
		i++;
	}
	len++;
	/* int	i;
	int	len;
	t_quote q;

	i = index;
	len = 0;
	q.q_closed = true; */
	/* if (is_quote(str[i]))
	{
		q.q_closed = false;
		q.type = str[i];
		i++;
	} */
	/* while (str[i] && (!is_delimiter(str[i], delim) || !q.q_closed))
	{
		if (str[i] == q.type && !q.q_closed)
		{
			q.q_closed = true;
			q.type = 0;
		}
		else if (q.q_closed && is_quote(str[i]))
		{
			q.q_closed = false;
			q.type = str[i];
		}
		len++;
		i++;
	}
	return (len); */
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
