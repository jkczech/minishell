#include "../include/minishell.h"

bool ft_is_seperator(char c)
{
	char *operator = ";&|><'=%";
	int i;

	i = 0;
	while(operator[i])
	{
		if(operator[i] == c)
			return (true);
		else
			i++;
	}
	return (false);
}

int token_count(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0')
    { 
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] != '\0' && !ft_is_seperator(str[i]))
        {
            count++;
            while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0' && !ft_is_seperator(str[i]))
                i++;
        }
		if((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&') || (str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			i++;
		if(ft_is_seperator(str[i]))
		{
			count++;
			i++;
		}
    }
    printf("Token count: %d\n", count);
    return count;
}

int count_chars(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			while(str[i] == ' ' || str[i] == '\t')
				i++;
		}
		if(str[i] != ' ' || str[i] != '\t')
		{
			count++;
			while(str[i] == ' ' || str[i] == '\t')
				i++;
		}
		i++;
	}
	printf("Char count: %d\n", count);
	return (count);
}

char *norm_input(char *str, int wc, int tc)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (wc + tc + 1));
	if(!result)
		return (NULL);
	while(i < (wc + tc))
	{
		if(str[j] == '"')
		{
			while(str[j] == '"')	
					j++;
		}
		if(str[j] == ' ' && str[j + 1] == ' ')
		{
			while(str[j] == ' ' && str[j + 1] == ' ')
				j++;
		}
		if(((ft_is_seperator(str[j]) && !ft_is_seperator(str[j - 1])) || str[j] == '-') && str[j - 1] != ' ' && j != 0)
		{
			result[i] = ' ';
			i++;
		}
		result[i] = str[j];
		i++;
		j++;
		if(j > 0 && (!ft_is_seperator(str[j]) && ft_is_seperator(str[j - 1])) && str[j] != ' ')
		{
			result[i] = ' ';
			i++;
		}
	}
	result[i] = '\0';
	printf("Normed input: %s\n", result);
	return (result);
}

int tokenlen(char *str)
{
	int i;

	i = 0;
	while(str[i] && (!ft_is_seperator(str[i]) && !ft_is_seperator(str[i + 1])))
				i++;
	return (i);
}

void create_single_operator_node(char *str, int i, t_token *token)
{
	token->content = malloc(sizeof(char) * 2);
	token->content[0] = str[i];
	token->content[1] = '\0';
	token->token = ft_detect_operator(str[i], 0);
}

void create_double_operator_node(char *str, int i, t_token *token)
{
	token->content = malloc(sizeof(char) * 2);
	token->content[0] = str[i];
	token->content[1] = str[i + 1];
	token->content[2] = '\0';
	token->token = ft_detect_operator(str[i], str[i + 1]);
}

void create_word_node(char *str, int i, t_token *token)
{
	int j;

	j = 0;
	token->content = malloc(sizeof(char) * tokenlen(&str[i]) + 1);
	token->token = WORD;
	while(!ft_is_seperator(str[i]) && str[i] != '\0')
	{
		token->content[j] = str[i];
		j++;
		i++;
	}
	token->content[j] = '\0';
	token->token = WORD;
}

char *create_str(char *str)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	printf("Tokenlen: %d\n", tokenlen(str));
	result = malloc(sizeof(char) * tokenlen(str) + 1);
	while(!ft_is_seperator(str[i]) && str[i] != '\0')
	{
		result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}


t_list *tokenizing(char *str)
{
	int i;
	int j;
	t_token *token;
	t_list *list;

	list = NULL;
	token = malloc(sizeof(t_token));
	i = 0;
	j = 0;
	while(str[i])
	{
		if(ft_is_seperator(str[i]) && !ft_is_seperator(str[i + 1]))
		{
			create_single_operator_node(str, i, token);
			ft_lstadd_back(&list, ft_lstnew(token));
			i++;
		}
		else if(ft_is_seperator(str[i]) && ft_is_seperator(str[i + 1]))
		{
			create_double_operator_node(str, i, token);
			ft_lstadd_back(&list, ft_lstnew(token));
			i += 2;
		}
		else if(!ft_is_seperator(str[i]))
		{
			create_word_node(str, i, token);
			ft_lstadd_back(&list, ft_lstnew(token));
			i++;
		}
		while(str[i] == ' ' && str[i] != '\0')
			i++;
	}
	free(token->content);
	return (list);
}


/* void tokenizing(char *str)
{
	static int *i;
	int j;
	t_token *token;

	token = malloc(sizeof(t_token));
	i = 0;
	j = 0;
	while(str[*i])
	{
		if(ft_is_seperator(str[*i]))
		{
			create_single_operator_node(str, &i, token);
			i++;
		}
		else if(!ft_is_seperator(str[*i]))
		{
			create_word_node(str, i, token);
			i++;
		}
		while(str[*i] == ' ' && str[*i] != '\0')
			i++;
	}
	free(token->content);
} */


void check_input(char *str)
{
	char *norm_str;
	//t_list *list;

	norm_str = norm_input(str, token_count(str), count_chars(str));
	if(!norm_str)
		return ;
	//list = tokenizing(norm_str);
	
	char *str_token = create_str(norm_str);

	printf("Token: %s\n", str_token);
	
	//free(norm_str);
}
