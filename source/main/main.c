/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:21 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/12 13:02:07 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	//t_list	*env_list;

	//env_list = NULL;
	shell = malloc(sizeof(t_shell));
	init_shell(shell, envp);
	if (argc < 0 || !argv)
		return (1);
	shell->envp = envp;
	shell->env_list = NULL;
	envp_into_list(shell->envp, shell->env_list);
	while(shell->env_list)
	{
		printf("%s\n", shell->env_list->content);
		shell->env_list = shell->env_list->next;
	}
	minishell(shell);
}

/* int	main(int argc, char **argv)
{
	if (argc < 1)
		return (1);
	printf("1st arg is: %s\n", argv[1]);
	return (0);
} */
