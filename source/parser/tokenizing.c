/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:42:17 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/12 15:34:05 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//process_quoted_token
void	process_quoted_token(char *str, int *index, char *token_content, int *j)
{
	token_content[*j] = str[*index];
	(*j)++;
	(*index)++;
	while (str[(*index)] != '"')
	{
		token_content[(*j)++] = str[*index];
		(*index)++;
	}
}

//process_pipe_token
void	process_pipe_token(int token_type, t_token **head,
t_token *new_token, char *token_content)
{
	free(token_content);
	token_content = NULL;
	new_token = create_token(NULL, token_type);
	add_token(head, new_token);
}

//creates a token
void	process_token(char *str, int *index, int token_type, t_token **head)
{
	t_token	*new_token;
	int		len;
	char	*token_content;
	int		j;

	new_token = NULL;
	len = token_len(str, *index, DELIMITER);
	if (str[*index] == '"')
		len = token_len(str, *index, "<>|");
	token_content = malloc(sizeof(char) * (len + 1));
	if (token_content == NULL)
		return ;
	j = 0;
	if (str[*index] == '"')
		process_quoted_token(str, index, token_content, &j);
	if (token_type == PIPE && is_delimiter(str[*index], DELIMITER))
	{
		process_pipe_token(token_type, head, new_token, token_content);
		return ;
	}
	while (str[*index] && !is_delimiter(str[*index], DELIMITER))
		token_content[j++] = str[(*index)++];
	token_content[j] = '\0';
	new_token = create_token(token_content, token_type);
	add_token(head, new_token);
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

//assigns token types, returns a list of tokens
t_token	*assign_token_types(t_shell *shell)
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
	return (head);
}
