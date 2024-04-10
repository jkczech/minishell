/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:13 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/10 12:35:46 by jkoupy           ###   ########.fr       */
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
	//int				hd_i;
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
}
/* void	free_iter(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->norm_input)
		free(shell->norm_input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmds(shell);
	if (shell->pipes)
		free_pipes(shell);
	if (shell->child_pids)
		free(shell->child_pids);
	while (shell->hd_i > 0)
	{
		unlink(ft_strjoin("heredocs/.heredoc", ft_itoa(shell->hd_i)));
		shell->hd_i--;
	}
} */