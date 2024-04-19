/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:42:17 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/19 21:02:13 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//process_quoted_token
void	process_quoted_token(char *str, int *index, char *token_content, int *j)
{
	char quote;

	quote = str[*index];	
	token_content[*j] = str[*index];
	(*j)++;
	(*index)++;
	while (quote != str[*index])
	{
		token_content[(*j)++] = str[*index];
		(*index)++;
	}
}

//creates a token
void	process_token(char *str, int *index, int token_type, t_token **head)
{
	t_token	*new_token;
	char	*token_content;
	int		j;
	//bool	is_quoted;
	t_quote	quote;

	//is_quoted = false;
	quote.q_closed = false;
	new_token = NULL;
	token_content = allocate_token_content(str, index);
	if (token_content == NULL)
		return ;
	j = 0;
	if (token_type == PIPE && is_delimiter(str[*index], DELIMITER))
		return (add_null_pipe(head, new_token, token_content));
	while (str[*index] && (!is_delimiter(str[*index], DELIMITER) || quote.q_closed))
	{
		if (is_quote(str[*index]))
		{
			quote.q_closed = !quote.q_closed;
			process_quoted_token(str, index, token_content, &j);
		}
		token_content[j++] = str[(*index)++];
	}
	token_content[j] = '\0';
	new_token = create_token(token_content, token_type);
	add_token(head, new_token);
}

char	*allocate_token_content(char *str, int *index)
{
	int		len;
	char	*token_content;

	len = token_len(str, *index, DELIMITER);
	if (is_quote(str[*index]))
		len = token_len(str, *index, "<>|");
	token_content = malloc(sizeof(char) * (len + 1));
	return (token_content);
}

//processes a pipe token
int	process_ttpipe(t_shell *shell, int *i, t_token *head, int token_type)
{
	if (shell->norm_input[*i] == ' ')
		(*i)++;
	if (is_sep(shell->norm_input[*i]))
	{
		process_token(shell->norm_input, i, token_type, &head);
		return (1);
	}
	return (0);
}

//create linked list of tokens, save it in shell->tokens
void	get_tokens(t_shell *shell)
{
	int		i;
	t_token	*head;
	int		token_type;

	i = 0;
	head = NULL;
	while (shell->norm_input[i])
	{
		token_type = what_token(shell->norm_input, i);
		if (token_type == HEREDOC || token_type == APPEND)
			i += 2;
		else if (token_type != WORD)
			i++;
		if (token_type == PIPE)
		{
			if (process_ttpipe(shell, &i, head, token_type) == 1)
				continue ;
		}
		skip_spaces(shell->norm_input, &i);
		process_token(shell->norm_input, &i, token_type, &head);
		if (shell->norm_input[i] != 0)
			i++;
	}
	shell->tokens = head;
}
