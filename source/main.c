/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:21 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/22 12:06:45 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	env_list = NULL;
	prompt = "🤏🐚: ";
	envp_into_list(envp, env_list);
	while(1)
	{
		input = readline(prompt);
		if(input)
		{
			check_input(input);
			if(strcmp(input, "history -c") == 0)
				rl_clear_history();
			else if(strcmp(input, "exit") == 0)
				exit(1);
			/* else if(strcmp(input, "env") == 0)
				print_list(env_list); */
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
