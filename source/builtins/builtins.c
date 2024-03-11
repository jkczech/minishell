/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/11 15:50:25 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//init path in pipex
bool init_path(t_shell *shell)
{
	char *path;

	path = get_path(shell);
	if (!path)
		return (false);
	shell->paths = ft_split(path, ':');
	if(path)
		free(path);
	if (!shell->paths)
		return (false);
	return (true);
}

//init all the shell variables
bool	init_shell(t_shell *shell, char **envp)
{
	shell->input = NULL;
	shell->norm_input = NULL;
	shell->tokens = NULL;
	shell->history = NULL;
	if (!copy_envp(shell, envp))
		return (false);
	init_path(shell);
	return (true);
}

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

void ft_free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if(shell->envp && shell->envp[i])
		ft_free_list(shell->env_list);
	if(shell->norm_input)
		free(shell->norm_input);
	if(shell->tokens)
		free_tokens(shell->tokens);
	if(shell->paths)
	{
		while (shell->paths[i])
		{
			free(shell->paths[i]);
			i++;
		}
		free(shell->paths);
	}
	//free_pipex(&shell->pipex);
	free(shell);
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if(tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	free(*tokens);
	*tokens = NULL;
}


