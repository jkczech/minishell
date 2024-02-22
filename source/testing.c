#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD 0
#define INPUT 1
#define OUTPUT 2
#define HEREDOC 3
#define APPEND 4
#define PIPE 5

typedef struct s_token
{
    char            *content;
    int             token;
    struct s_token  *next;
    struct s_token  *prev;
}               t_token;


void add_token(t_token **head, char *content, int token_type) {
    t_token *new_node = malloc(sizeof(t_token));
    if (new_node) {
        new_node->content = strdup(content);
        new_node->token = token_type;
        new_node->next = NULL;

        if (*head == NULL) {
            *head = new_node;
        } else {
            t_token *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
}

void assign_token_types(char *input) {
    char *token;
    t_token *head = NULL;
    int output_flag = 0; // Flag, um sicherzustellen, dass nur das erste Wort nach '>' als OUTPUT betrachtet wird

    while ((token = strtok(input, " ")) != NULL) {
        if (strcmp(token, "<") == 0) {
            // Setze das Token-Typ auf INPUT
            add_token(&head, strtok(NULL, " "), INPUT);
        } else if (strcmp(token, ">") == 0) {
            // Setze das Flag, um zu signalisieren, dass OUTPUT verarbeitet wird
            output_flag = 1;
        } else if (strcmp(token, "|") == 0) {
            // Nichts tun, da '|' kein Wort ist
        } else {
            if (output_flag) {
                // Setze das Token-Typ auf OUTPUT und setze das Flag zurück
                add_token(&head, token, OUTPUT);
                output_flag = 0;
            } else {
                // Setze das Token-Typ auf WORD
                add_token(&head, token, WORD);
            }
        }
        input = NULL; // Setze strtok beim nächsten Aufruf fort
    }

    // Ausgabe der gespeicherten Tokens zur Überprüfung
    t_token *current = head;
    while (current != NULL) {
        printf("%s = %s\n", current->content, current->token == INPUT ? "INPUT" : (current->token == OUTPUT ? "OUTPUT" : "WORD"));
        current = current->next;
    }

    // Speicher freigeben
    while (head != NULL) {
        t_token *tmp = head;
        head = head->next;
        free(tmp->content);
        free(tmp);
    }
}


int main() {
    char input[] = "< Input cat -l | grep \"Hello\" >Output";
    assign_token_types(input);
    return 0;
}
/* int is_delimiter(char c, const char *delim)
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



int token_len(char *str, const char *delim)
{
	int i;

	i = 0;
	while(str[i] && !is_delimiter(str[i], delim))
		i++;
	return (i);
}

void assign_token_types(char *str)
{
    int token_type;
	int i;
	int j;

	j = 0;
	i = 0;

	while(str[i])
	{
		if(str[i] == '<')
		{
			while(j < token_len(&str[i], " |<>"))
				i++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
    int i;

    i = 1;

    if(argc < 2)
    {
        printf("Usage: %s <string>\n", argv[0]);
        return (1);
    }
    assign_token_types(argv[1]);
    return (0);
} */