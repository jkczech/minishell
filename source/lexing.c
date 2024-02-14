#include "../include/minishell.h"

bool ft_is_seperator(char c)
{
	char *operator = ";&|><'=!{}()[]";
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

void skip_spaces(char *str)
{
	int i;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
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
		if(ft_is_seperator(str[i]) || (ft_is_seperator(str[i + 1]) && ft_is_seperator(str[i])))
		{
			count++;
			i++;
		}
    }

    printf("Token count: %d\n", count);
    return count;
}

void check_input (char *str)
{
	int i;

	i = 0;
	token_count(str);
	while(str[i])
	{
		while((str[i] >= 9 && str[i] <= 13) && str[i] == ' ')
			i++;
		printf("Str[i]: %c\n", str[i]);
		if(ft_is_seperator(str[i]))
			printf("Seperator/Operator found!\n");
		i++;
	}
}


int main(int argc, char **argv)
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
}