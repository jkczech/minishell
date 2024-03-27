/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:13 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/27 11:59:04 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* typedef struct s_shell
{
	t_list			*env_list;
	t_list			*history;
	char			**envp;
	char			**paths;
	int				exitcode;
	char			*input;
	char			*norm_input;
	int				size;
	t_token			**tokens;
	t_cmd			*cmds;
	int				**pipes;
	int				*child_pids;
	bool			heredoc; //
	//int				heredoc_index; //hd_i
}	t_shell; */

//init all the shell variables
bool	init_shell(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	shell->history = NULL;
	shell->envp = envp;
	shell->paths = NULL;
	init_path(shell);
	if (!shell->paths)
		return (false);
	shell->exitcode = 0;
	shell->input = NULL;
	shell->norm_input = NULL;
	shell->size = 0;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->pipes = NULL;
	shell->child_pids = NULL;
	shell->heredoc = false;
	return (true);
}

//init path in shell
bool	init_path(t_shell *shell)
{
	char	*path;

	path = get_path(shell);
	if (!path)
		return (false);
	shell->paths = ft_split(path, ':');
	if (path)
		free(path);
	if (!shell->paths)
		return (false);
	return (true);
}

//allocate memory for commands table 
//and initialize it
bool	init_cmds(t_shell *shell)
{
	int	i;

	shell->cmds = malloc(sizeof(t_cmd) * shell->size);
	if (!shell->cmds)
		return (false);
	i = 0;
	while (i < shell->size)
	{
		shell->cmds[i].args = NULL;
		shell->cmds[i].path = NULL;
		shell->cmds[i].found = false;
		shell->cmds[i].input = STDIN_FILENO;
		shell->cmds[i].output = STDOUT_FILENO;
		i++;
	}
	return (true);
}
