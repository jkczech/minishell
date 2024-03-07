/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:42:17 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/07 10:55:46 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//creates a token
void	process_token(char *str, int *index, int token_type, t_token **head)
{
	t_token	*new_token;
	int		len;
	char	*token_content;
	int		j;

	new_token = NULL;
	len = token_len(str, *index, DELIMITER);
	token_content = malloc(sizeof(char) * (len + 1));
	if (token_content == NULL)
		return ;
	j = 0;
	if (str[*index] == '"')
	{
		token_content[j++] = '"';
		while (str[(*index)++] != '"')
			token_content[j++] = str[*index];
	}
	if (token_type == PIPE && is_delimiter(str[*index], DELIMITER))
	{
		new_token = create_token(NULL, token_type);
		add_token(head, new_token);
		return ;
	}
	while (str[*index] && !is_delimiter(str[*index], DELIMITER))
		token_content[j++] = str[(*index)++];
	token_content[j] = '\0';
	new_token = create_token(token_content, token_type);
	add_token(head, new_token);
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
			if (shell->norm_input[i] == ' ')
				i++;
			if (is_sep(shell->norm_input[i]))
			{
				process_token(shell->norm_input, &i, token_type, &head);
				continue ;
			}
		}
		skip_spaces(shell->norm_input, &i);
		process_token(shell->norm_input, &i, token_type, &head);
		if (shell->norm_input[i] != 0)
			i++;
	}
	return (head);
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
