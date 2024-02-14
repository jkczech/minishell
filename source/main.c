/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:21 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/09 15:39:29 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_list(t_list *list)
{
	while(list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}

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
//Jakob
void envp_into_list(char **envp, t_list *env_list)
{
	int i;

	i = 0;
	env_list = NULL;
	while(envp[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(envp[i]));
		i++;
	}
	//print_list(env_list);
}

void minishell(char **envp, t_list *env_list)
{
	char *input;
	char *prompt;
	//int i;

	env_list = NULL;
	//i = 0;
	prompt = "Mini🐚: ";
	envp_into_list(envp, env_list);
	while(1)
	{
		input = readline(prompt);
		if(input)
		{
			if(strcmp(input, "history -c") == 0)
				rl_clear_history();
			else if(strcmp(input, "exit") == 0)
				exit(1);
			else if(strcmp(input, "env") == 0)
				print_list(env_list);
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
	(void)**argv;
	t_list *env_list;

	env_list = NULL;
	minishell(envp, env_list);	
}

/* int	main(int argc, char **argv)
{
	if (argc < 1)
		return (1);
	printf("1st arg is: %s\n", argv[1]);
	return (0);
} */
