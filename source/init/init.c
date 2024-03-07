/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:13 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/07 10:28:58 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	init_shell(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	shell->envp = envp;
	shell->env_list = NULL;
	shell->envp = NULL;
	return (true);
}

//initialize pipex structure
//get_tokens to pipex->tokens
/* bool	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->paths = NULL;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmds = NULL;
	pipex->s_cmds = NULL;
	pipex->pipes = NULL;
	pipex->envp = envp;
	pipex->child_pids = NULL;
	pipex->exitcode = EXIT_SUCCESS;
	pipex->tokens = NULL;
	pipex->size = -1; //calculate
	if (!init_cmds(pipex))
		return (false);
	if (!init_s_cmds(pipex))
		return (false);
	return (true);
}

//help pipex init
//allocate memory for commands
bool	init_cmds(t_pipex *pipex)
{
	int	i;

	pipex->cmds = malloc(pipex->size * sizeof(t_cmd));
	if (!pipex->cmds)
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pipex->cmds[i].args = NULL;
		pipex->cmds[i].found = false;
		pipex->cmds[i].path = NULL;
		i++;
	}
	return (true);
}
 */