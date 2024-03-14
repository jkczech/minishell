/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:42:26 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/13 17:31:35 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//free double pointer
void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	printf("HERE\n");
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	ft_free_list(t_list *list)
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
	if (shell->envp && shell->envp[i])
		ft_free_list(shell->env_list);
	if (shell->norm_input)
		free(shell->norm_input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->paths)
	{
		while (shell->paths[i])
		{
			free(shell->paths[i]);
			i++;
		}
		free(shell->paths);
	}
	free(shell);
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
