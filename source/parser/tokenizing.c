/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:42:17 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/13 12:27:20 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//copy token content to a new string
void	copy_token_content(char *token_content, char *str, int *i)
{
	t_quote	quote;
	int		j;

	quote.in_quotes = false;
	quote.type = 0;
	j = 0;
	while (str[*i] && (!is_delimiter(str[*i], DELIMITER) || quote.in_quotes))
	{
		if (is_quote(str[*i]) && !quote.in_quotes)
		{
			quote.type = str[*i];
			token_content[j++] = str[(*i)++];
			while (quote.type != str[*i])
				token_content[j++] = str[(*i)++];
			token_content[j++] = str[(*i)++];
			continue ;
		}
		token_content[j++] = str[(*i)++];
	}
	token_content[j++] = '\0';
}

//creates a token
void	process_token(char *str, int *i, int token_type, t_token **head)
{
	t_token	*new_token;
	char	*token_content;

	new_token = NULL;
	token_content = NULL;
	token_content = allocate_token_content(str, i);
	if (token_content == NULL)
		return ;
	if (token_type == PIPE && is_delimiter(str[*i], DELIMITER))
		return (add_null_pipe(head, new_token, token_content));
	copy_token_content(token_content, str, i);
	new_token = create_token(token_content, token_type);
	add_token(head, new_token);
}

char	*allocate_token_content(char *str, int *index)
{
	int		len;
	char	*token_content;

	len = token_len(str, *index, DELIMITER);
	token_content = malloc(sizeof(char) * (len));
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
