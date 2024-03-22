/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:23 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/21 16:05:01 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//	envp_into_list(shell->envp, shell->env_list);
//	while (shell->env_list)
//	{
//		printf("%s\n", shell->env_list->content);
//		shell->env_list = shell->env_list->next;
//	}

//Save the environment variables in a list

t_list	*create_node(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

bool	envp_into_list(char **envp, t_list **env_list)
{
	int		i;
	t_list	*node;

	i = 0;
	node = NULL;
	while (envp[i])
	{
		node = ft_lstnew_l(envp[i]);
		if (!node)
			return (false);
		ft_lstadd_back(env_list, node);
		i++;
	}
	return (true);
}

//Prints the environment variables
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

void	env_command(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (args_counter(cmd->args) > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("´", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("´", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exitcode = 127;
		return ;
	}
	print_env_list(shell->env_list);
}
