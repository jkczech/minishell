/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:21 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/09 13:27:09 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void word_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			count++;
			while(str[i] == ' ' || str[i] == '\t')
				i++;
		}
		i++;
	}
	printf("Word count: %d\n", count);
}

void check_input (char *str)
{
	int i;

	i = 0;
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

void minishell(char **envp)
{
	char *input;
	char *prompt;
	int i;

	i = 0;
	prompt = "Mini🐚: ";
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	while(1)
	{
		input = readline(prompt);
		if(input)
		{
			if(strcmp(input, "history -c") == 0)
				rl_clear_history();
			else if(strcmp(input, "exit") == 0)
				exit(1);
			add_history(input);
			free(input);
		}
		else
			break;
	}
}

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	minishell(envp);	
}

/* int	main(int argc, char **argv)
{
	if (argc < 1)
		return (1);
	printf("1st arg is: %s\n", argv[1]);
	return (0);
} */
