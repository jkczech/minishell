/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:22:02 by jseidere          #+#    #+#             */
/*   Updated: 2024/02/22 09:54:46 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *create_node(char *content) {
    t_token *node = malloc(sizeof(t_token));
    if (node) {
        node->content = ft_strdup(content);
        node->next = NULL;
    }
    return node;
}

void free_list(t_token *head) {
	t_token *tmp;
	while (head) {
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

char *ft_strtok(char *str, const char *delim)
{
	static char *s;
	char *begin;
	char *end;

	if (str)
		s = str;
	if (!s)
		return (NULL);
	begin = s;
	while (*s)
	{
		if (ft_strchr(delim, *s))
		{
			*s = '\0';
			s++;
			return (begin);
		}
		s++;
	}
	end = s;
	s = NULL;
	return (begin);
}

