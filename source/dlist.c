/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:54:49 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/22 13:10:12 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*create_token(char *content, int token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token != NULL)
	{
		new_token->content = content;
		new_token->token = token;
		new_token->prev = NULL;
		new_token->next = NULL;
	}
	return (new_token);
}

void	destroy_token(t_token *token)
{
	if (token != NULL)
	{
		free(token->content);
		free(token->next);
		free(token->prev);
		free(token);
	}
}

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		destroy_token(current);
		current = next;
	}
	*head = NULL;
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
		new_token->prev = current;
	}
}
/*
void	remove_token(t_token **head, t_token *token)
{
	if (*head == token)
		*head = token->next;
	if (token->next != NULL)
		token->next->prev = token->prev;
	if (token->prev != NULL)
		token->prev->next = token->next;
	destroy_token(token);
}
*/
