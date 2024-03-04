/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/04 10:55:27 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
bool	copy_envp(t_shell *shell, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	shell->envp = malloc(sizeof(char *) * (len + 1));
	if (!shell->envp)
		return (false);
	while (i < len)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
			return (false);
		i++;
	}
	shell->envp[i] = NULL;
	return (true);
}

char	*get_path(t_shell *shell)
{
	int		i;
	char	*path;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(shell->envp[i] + 5);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

bool	init_shell(t_shell *shell, char **envp)
{
	shell->envp = NULL;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->history = NULL;
	if (!copy_envp(shell, envp))
		return (false);
	shell->pipex.paths = ft_split(get_path(shell), ':');
	if (!shell->pipex.paths)
		return (false);
	return (true);
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
	free(shell->line);
	free_tokens(shell->tokens);
	free_pipex(&shell->pipex);
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = next;
	}
	*tokens = NULL;
}
*/
