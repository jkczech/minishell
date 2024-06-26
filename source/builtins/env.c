/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:23 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/15 15:50:35 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//create new environment variable
t_env	*ft_fillenv(char *str)
{
	t_env	*ret;
	int		i;

	i = 0;
	ret = (t_env *)malloc(sizeof(t_env));
	if (!ret)
		return (0);
	if (check_env_var(str))
		ret->flag = 1;
	else
		ret->flag = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret->var = ft_substr(str, 0, i);
	if (!ret->var)
		return (0);
	ret->value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	if (!ret->value)
	{
		free(ret->var);
		free(ret);
		return (0);
	}
	return (ret);
}

//create new list element
t_list	*ft_envnew_l(void *content)
{
	t_list	*list;

	if (!content)
		return (0);
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = (void *)ft_fillenv(content);
	if (!list->content)
	{
		free(list);
		return (0);
	}
	list->next = NULL;
	return (list);
}

//init the environment variables
bool	envp_into_list(char **envp, t_list **env_list)
{
	int		i;
	t_list	*node;

	i = 0;
	node = NULL;
	while (envp[i])
	{
		node = ft_lstnew(ft_fillenv(envp[i]));
		if (!node)
			return (false);
		ft_lstadd_back(env_list, node);
		i++;
	}
	return (true);
}

//print the environment variables
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

//Handles the env command
void	env_command(t_shell *shell, t_cmd *cmd, int out)
{
	if (count_args(cmd->args) > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("´", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("´", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exitcode = 127;
		return ;
	}
	print_env_list(shell->env_list, out);
}
