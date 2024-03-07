/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:47:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/07 10:55:59 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>
/* 
int	main(void)
{
	char	*input;

    input = malloc(sizeof(char) * 100);

    strcpy(input, "< In "cat -l" >> App | grep Hello | > Ser << Again > Out"); 
    //14 Spaces
    assign_token_types(input);
	return (0);
}
*/
/* char *assign_token_types(char *str)
{
    int i;
    int j;
    char *token;
    t_token *head;
    t_token *node;

    i = 0;
    j = 0;
    head = NULL;

    while(str[i])
    {
        if(str[i] == '<' && str[i + 1] == '<')
        {
            i += 2;
            if(str[i] == ' ')
                i++;
            int len = token_len(str, i, " |<>");
            //printf("Tokenlen: %d\n", len);
            token = malloc(sizeof(char) * (len + 1));
            if(token == NULL)
                return (NULL);
            int j = 0;
            while(str[i] && !is_delimiter(str[i], " |<>"))
                token[j++] = str[i++];
            token[j] = '\0';
            node = create_token(token, HEREDOC);
            add_token(&head, node);
            printf("Token: %d\n", node->token);
            printf("Token: %s\n", node->content);
            free(token);
        }
        else if(str[i] == '>' && str[i + 1] == '>')
        {
            i += 2;
            if(str[i] == ' ')
                i++;
            int len = token_len(str, i, " |<>");
            //printf("Tokenlen: %d\n", len);
            token = malloc(sizeof(char) * (len + 1));
            if(token == NULL)
                return (NULL);
            int j = 0;
            while(str[i] && !is_delimiter(str[i], " |<>"))
                token[j++] = str[i++];
            token[j] = '\0';
            node = create_token(token, APPEND);
            add_token(&head, node);
            printf("Token: %d\n", node->token);
            printf("Token: %s\n", node->content);
            free(token);
        }
        else if(str[i] == '<')
        {
            i++;
            if(str[i] == ' ')
                i++;
            int len = token_len(str, i, " |<>");
            //printf("Tokenlen: %d\n", len);
            token = malloc(sizeof(char) * (len + 1));
            if(token == NULL)
                return (NULL);
            int j = 0;
            while(str[i] && !is_delimiter(str[i], " |<>"))
                token[j++] = str[i++];
            token[j] = '\0';
            node = create_token(token, INPUT);
            add_token(&head, node);
            printf("Token: %d\n", node->token);
            printf("Token: %s\n", node->content);
            free(token);
        }
        else if(str[i] == '>')
        {
            i++;
            if(str[i] == ' ')
                i++;
            int len = token_len(str, i, " |<>");
            //printf("Tokenlen: %d\n", len);
            token = malloc(sizeof(char) * (len + 1));
            if(token == NULL)
                return (NULL);
            int j = 0;
            while(str[i] && !is_delimiter(str[i], " |<>"))
                token[j++] = str[i++];
            token[j] = '\0';
            node = create_token(token, OUTPUT);
            add_token(&head, node);
            printf("Token: %d\n", node->token);
            printf("Token: %s\n", node->content);
            free(token);
        }
        else if(str[i] == '|')
        {
            i++;
            if(str[i] == ' ')
                i++;
            int len = token_len(str, i, " |<>");
            //printf("Tokenlen: %d\n", len);
            token = malloc(sizeof(char) * (len + 1));
            if(token == NULL)
                return (NULL);
            int j = 0;
            while(str[i] && !is_delimiter(str[i], " |<>"))
                token[j++] = str[i++];
            token[j] = '\0';
            node = create_token(token, WORD);
            add_token(&head, node);
            printf("Token: %d\n", node->token);
            printf("Token: %s\n", node->content);
            free(token);
        }
        else
        {
            int len = token_len(str, i, " |<>");
            //printf("Tokenlen: %d\n", len);
            token = malloc(sizeof(char) * (len + 1));
            if(token == NULL)
                return (NULL);
            int j = 0;
            while(str[i] && !is_delimiter(str[i], " |<>"))
                token[j++] = str[i++];
            token[j] = '\0';
            node = create_token(token, WORD);
            add_token(&head, node);
            printf("Token: %d\n", node->token);
            printf("Token: %s\n", node->content);
            free(token);
        
        }
        i++;
    }
        print_tokens(&head);
} */
