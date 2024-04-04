/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:54:49 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/01 17:10:27 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(char *content, int token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token != NULL)
	{
		new_token->content = content;
		new_token->token = token;
		new_token->next = NULL;
	}
	return (new_token);
}

void	destroy_token(t_token *token)
{
	if (token != NULL)
	{
		free(token->content);
		free(token);
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(tokens);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

void	remove_token(t_token **head, t_token *token)
{
	t_token	*current;

	if (*head == NULL || token == NULL)
		return ;
	if (*head == token)
		*head = token->next;
	else
	{
		current = *head;
		while (current->next != token)
			current = current->next;
		current->next = token->next;
	}
	destroy_token(token);
}
