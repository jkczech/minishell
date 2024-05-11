/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:21:18 by jakob             #+#    #+#             */
/*   Updated: 2024/05/11 19:05:26 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_env_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**envp_list_into_char(t_list *env_list)
{
	t_list	*tmp;
	char	**envp;
	int		i;

	tmp = env_list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i] = ft_strjoin3(((t_env *)env_list->content)->var, "=",
				((t_env *)env_list->content)->value);
		if (!envp[i])
			return (NULL);
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

//sort environment export in alphabetical order
void	sort_env(t_shell *shell)
{
	t_list	*t;
	t_list	*t2;
	char	*tmp_str;

	t = shell->env_list;
	while (t)
	{
		t2 = t->next;
		while (t2)
		{
			if (ft_strncmp(((t_env *)t->content)->var,
					((t_env *)t2->content)->var,
					ft_strlen(((t_env *)t->content)->var)) > 0)
			{
				tmp_str = ((t_env *)t->content)->var;
				((t_env *)t->content)->var = ((t_env *)t2->content)->var;
				((t_env *)t2->content)->var = tmp_str;
				tmp_str = ((t_env *)t->content)->value;
				((t_env *)t->content)->value = ((t_env *)t2->content)->value;
				((t_env *)t2->content)->value = tmp_str;
			}
			t2 = t2->next;
		}
		t = t->next;
	}
}
