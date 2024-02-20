#include "../include/minishell.h"

bool ft_is_seperator(char c)
{
	char *operator = ";&|><'=!%";
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


bool check_doubles_seperators(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '|' && str[i + 1] == '|')
			return (true);
		else if (str[i] == '&' && str[i + 1] == '&')
			return (true);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (true);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (true);
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
	result = malloc(sizeof(char) * wc + tc);
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
		if((!ft_is_seperator(str[j]) && ft_is_seperator(str[j - 1])) && str[j] != ' ')
		{
			result[i] = ' ';
			i++;
		}
	}
	result[wc + tc] = '\0';
	printf("Normed input: %s\n", result);
	return (result);
}

void check_input(char *str)
{
	int i;
	char *norm_str;

	i = 0;
	norm_str = norm_input(str, token_count(str), count_chars(str));
	if(!norm_str)
		return ;
	while(norm_str[i])
	{
		if(ft_is_seperator(norm_str[i]) && ft_is_seperator(norm_str[i + 1]))
		{
			printf("Operator: %c%c\n", norm_str[i], norm_str[i + 1]);
			i++;
			i++;
		}
		else if(ft_is_seperator(norm_str[i]))
		{
			printf("Operator: %c\n", norm_str[i]);
			i++;
		}
		else
		{
			printf("Word: ");
			while(norm_str[i] != ' ' && norm_str[i])
			{
				printf("%c", norm_str[i]);
				i++;
			}
			printf("\n");
		}
		while(norm_str[i] == ' ' && norm_str[i] != '\0')
			i++;
	}
	//free(norm_str);
}



/* int main(int argc, char **argv)
{
    if (argc < 1)
    {
        return (1);
    }
    else if (argc == 2)
    {
        check_input(argv[1]);
    }
    return (0);
} */