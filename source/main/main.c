/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:21 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/15 22:23:00 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	argc_check(argc, argv);
	init_shell(&shell, envp);
	minishell(&shell);
	return (shell.exitcode);
}

void	argc_check(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit(EXIT_SUCCESS);
	}
	if (count_args(argv) > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit(EXIT_SUCCESS);
	}
}
