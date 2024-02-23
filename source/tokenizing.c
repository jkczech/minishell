/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:42:17 by jseidere          #+#    #+#             */
/*   Updated: 2024/02/23 14:54:59 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_delimiter(char c, const char *delim)
{
	int i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int token_len(char *str, int index, const char *delim)
{
	int i;
    int len;

	i = index;
    len = 0;
	while(str[i] && !is_delimiter(str[i], delim))
    {
        len++;
        i++;
    }
	return (len);
}

void skip_spaces(char *str, int *index)
{
    while (str[*index] && str[*index] == ' ')
        (*index)++;
}

void process_token(char *str, int *index, int token_type, t_token **head)
{
    t_token *new_token;
    int len;
    char *token_content;

    new_token = NULL;
    len = token_len(str, *index, " |<>");
    token_content = malloc(sizeof(char) * (len + 1));
    if (token_content == NULL)
        return;
    int j = 0;
    while (str[*index] && !is_delimiter(str[*index], " |<>"))
        token_content[j++] = str[(*index)++];
    token_content[j] = '\0';
    new_token = create_token(token_content, token_type);
    add_token(head, new_token);
    free(token_content);
}

void print_list(t_token *head)
{
	while (head) {
		printf("%s\n", head->content);
		head = head->next;
	}
}

t_token *assign_token_types(char *str)
{
    int i = 0;
    t_token *head = NULL;

    while (str[i]) {
        if (str[i] == '<' && str[i + 1] == '<')
        {
            i += 2;
            skip_spaces(str, &i);
            process_token(str, &i, HEREDOC, &head);
        }
        else if (str[i] == '>' && str[i + 1] == '>')
        {
            i += 2;
            skip_spaces(str, &i);
            process_token(str, &i, APPEND, &head);
        } else if (str[i] == '<')
        {
            i++;
            skip_spaces(str, &i);
            process_token(str, &i, INPUT, &head);
        } else if (str[i] == '>')
        {
            i++;
            skip_spaces(str, &i);
            process_token(str, &i, OUTPUT, &head);
        } else if (str[i] == '|')
        {
            i++;
            skip_spaces(str, &i);
            process_token(str, &i, WORD, &head);
        } else {
            process_token(str, &i, WORD, &head);
        }
        i++;
    }
    printf("Tokens:%s\n", head->content);
    //print_tokens(&head);
    return (head);
}

/* int main() {
    char input[] = "< Input cat -l >> Append | grep \"Hello\" | Servus << Again > Output";
    assign_token_types(input);
    return 0;
} */