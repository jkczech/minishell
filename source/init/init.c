/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:13 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/06 15:34:34 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->child_pids = NULL;
	pipex->exitcode = EXIT_SUCCESS;
	pipex->heredoc = false;
	pipex->tokens = NULL;
	if (ft_strncmp(pipex->argv[1], "here_doc", 9) == 0
		&& ft_strncmp(pipex->argv[0], "./pipex_bonus", 14) == 0)
		pipex->heredoc = true;
	pipex->size = argc - 3 - pipex->heredoc;
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