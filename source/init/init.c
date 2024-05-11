/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:13 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/11 18:59:36 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* typedef struct s_shell
{
	t_list			*env_list;
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
	//int				hd_i;
}	t_shell; */

//init all the shell variables
bool	init_shell(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	shell->envp = copy_array(envp);
	if (!shell->envp)
		return (false);
	shell->env_list = NULL;
	envp_into_list(envp, &shell->env_list);
	shell->paths = NULL;
	init_path(shell);
	if (!shell->paths)
		return (false);
	shell->exitcode = 0;
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
		if (i == 0)
			shell->cmds[i].input = STDIN_FILENO;
		else
			shell->cmds[i].input = -1;
		if (i == shell->size - 1)
			shell->cmds[i].output = STDOUT_FILENO;
		else
			shell->cmds[i].output = -1;
		i++;
	}
	return (true);
}

void	init_iter(t_shell *shell)
{
	shell->input = NULL;
	shell->norm_input = NULL;
	shell->size = 0;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->pipes = NULL;
	shell->child_pids = NULL;
	shell->hd_i = 0;
	if (shell->envp)
		free_array(shell->envp);
	shell->envp = envp_list_into_char(shell->env_list);
}
