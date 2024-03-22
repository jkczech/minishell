/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:21 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/21 16:05:26 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	shell = malloc(sizeof(t_shell));
	init_shell(shell, envp);
	if (argc < 0 || !argv)
		return (1);
	shell->envp = envp;
	shell->env_list = NULL;
	envp_into_list(envp, &shell->env_list);
	shell->exitcode = 99;
	minishell(shell);
}
