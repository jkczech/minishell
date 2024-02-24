/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:22:02 by jseidere          #+#    #+#             */
/*   Updated: 2024/02/24 15:11:20 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/* char *ft_strtok(char *str, const char *delim)
{
	static char *s;
	char *begin;
	char *end;

	if (str)
		s = str;
	if (!s)
		return (NULL);
	while(*s && is_delimiter(*s, " "))
		s++;
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
} */

int	determine_token_type(char *token)
{
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUTPUT);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (INPUT);
	else if (ft_strncmp(token, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "||", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC);
	else
		return (WORD);
}

/* char *ft_strtok(char *str, const char *delim)
{
	static char *s;
	char *begin;
	char *end;
	char single_delim;
	t_token *token;

	if (str)
		s = str;
	if (!s)
		return (NULL);
	//Check witch delimiter is current and safe it in token
	while(*s && is_delimiter(*s, " "))
		s++;
	begin = s;
	while (*s)
	{
		if (is_delimiter(*s, delim))
		{
			single_delim = *s;
			token = malloc(sizeof(t_token));
			if(!token)
				return (NULL);
			*s = '\0';
			token->content = begin;
			if(single_delim == '>')
				token->token = REDIR_OUT;
			token->token = determine_token_type(begin);
			token->next = NULL;
			s++;
			return (begin);
		}
		s++;
	}
	end = s;
	s = NULL;
	return (begin);
} */

/* 
t_token	*create_node(char *content)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node)
	{
		node->content = ft_strdup(content);
		node->next = NULL;
		//node->prev = NULL;
	}
	return node;
}

void	ft_free_list(t_token *head)
{
	t_token *tmp;
	while (head) {
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

void	print_list(t_token *head)
{
	while (head) {
		printf("%s\n", head->content);
		head = head->next;
	}
} 
*/

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*begin;
	char		*end;

	if (str)
		s = str;
	if (!s)
		return (NULL);
	while (*s && is_delimiter(*s, " "))
		s++;
	begin = s;
	while (*s)
	{
		if (is_delimiter(*s, delim))
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
/* char *detect_token(char *str)
{
	static char *s;
	int i;
	int token_type;
	char *begin;
	char *end;

	i = 0;
	if (str)
		s = str;
	if (!s)
		return (NULL);

	while (*s && is_delimiter(*s, " "))
		s++;
	begin = s;
	while(s[i])
	{
		if(is_delimiter(s[i], "<>|"))
		{
			if(s[i] == '<' && s[i + 1] == '<')
				token_type = HEREDOC;
			else if(s[i] == '>' && s[i + 1] == '>')
				token_type = APPEND;			
			else if(s[i] == '<')
				token_type = INPUT;
			else if(s[i] == '>') 
				token_type = OUTPUT;
			else if(s[i] == '|')
				token_type = PIPE;
		}
	}
} */

//Check witch delimiter is current and save it in token
t_token	*split_and_store(char *input, char *delimiter)
{
	t_token	*head;
	t_token	*node;
	char	*token;

	head = NULL;
	token = ft_strtok(input, delimiter);
	while (token)
	{
		node = create_node(token);
		if (node == NULL)
			return (free_token_list(head), NULL);
		add_token(&head, node);
		token = ft_strtok(NULL, delimiter);
	}
	return (head);
}

/*
previous split_and_store

t_token	*split_and_store(char *input, char *delimiter)
{
	t_token	*head;
	t_token	*node;
	t_token	*current;
	char	*token;

	head = NULL;
	token = ft_strtok(input, delimiter);
	while (token)
	{
		node = create_node(token);
		if (node == NULL)
		{
			ft_free_list(head);
			return (NULL);
		}
		if (head == NULL)
			head = node;
		else
		{
			current = head;
			while (current->next)
				current = current->next;
			current->next = node;
		}
		token = ft_strtok(NULL, delimiter);
	}
	return (head);
}
*/
