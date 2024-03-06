/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:34:37 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/05 14:44:57 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* 
//the difference from main.c is the argc check
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_putstr_fd(ERR_ARG_2, 2), EXIT_FAILURE);
	if (!pipex_init(&pipex, argc, argv, envp))
		return (free_pipex(&pipex), error_message(NULL), EXIT_FAILURE);
	if (argc < 5 + pipex.heredoc)
		return (ft_putstr_fd(ERR_ARG_2, 2), free_pipex(&pipex), EXIT_FAILURE);
	if (!parse_input(&pipex))
		return (free_pipex(&pipex), EXIT_FAILURE);
	if (!create_pipes(&pipex))
		return (free_pipex(&pipex), error_message(NULL), EXIT_FAILURE);
	if (!execute(&pipex))
		return (free_pipex(&pipex), error_message(NULL), pipex.exitcode);
	free_pipex(&pipex);
	return (pipex.exitcode);
}
 */
