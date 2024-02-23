#include "../include/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD 0
#define INPUT 1
#define OUTPUT 2
#define HEREDOC 3
#define APPEND 4
#define PIPE 5

/* typedef struct s_token
{
    char            *content;
    int             token;
    struct s_token  *next;
    struct s_token  *prev;
}               t_token;
 */

void	print_tokens(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (token->token == WORD)
			ft_putstr_fd("\033[0;32m", 1);
		else if (token->token == INPUT)
			ft_putstr_fd("\033[0;34m", 1);
		else if (token->token == OUTPUT)
			ft_putstr_fd("\033[0;33m", 1);
		else if (token->token == HEREDOC)
			ft_putstr_fd("\033[0;35m", 1);
		else if (token->token == APPEND)
			ft_putstr_fd("\033[0;36m", 1);
		ft_putstr_fd(token->content, 1);
		ft_putstr_fd("\033[0m", 1);
		ft_putstr_fd("+", 1);
		token = token->next;
	}
	ft_putstr_fd("\n", 1);
}

t_token	*create_token(char *content, int token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token != NULL)
	{
		new_token->content = ft_strdup(content);
		new_token->token = token;
		new_token->prev = NULL;
		new_token->next = NULL;
	}
	return (new_token);
}

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



void skip_spaces(char *str, int *index) {
    while (str[*index] && str[*index] == ' ')
        (*index)++;
}

void process_token(char *str, int *index, int token_type, t_token **head) {
    int len = token_len(str, *index, " |<>");
    char *token_content = malloc(sizeof(char) * (len + 1));
    if (token_content == NULL)
        return;
    int j = 0;
    while (str[*index] && !is_delimiter(str[*index], " |<>"))
        token_content[j++] = str[(*index)++];
    token_content[j] = '\0';
    t_token *new_token = create_token(token_content, token_type);
    add_token(head, new_token);
    free(token_content);
}

char *assign_token_types(char *str)
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
    print_tokens(&head);
    return NULL;
}

int main() {
    char input[] = "< Input cat -l >> Append | grep \"Hello\" | Servus << Again > Output";
    assign_token_types(input);
    return 0;
}
//cc testing.c -g ../library/libft/source/ft_strdup.c ../library/libft/source/ft_strlen.c ../library/libft/source/ft_putstr_fd.c ../library/libft/source/ft_putchar_fd.c 





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