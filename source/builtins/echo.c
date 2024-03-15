/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:17:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/15 11:37:39 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo_command(t_shell *shell)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	printf("echo\n");
	if (shell->tokens[i] && ft_strncmp(shell->tokens[i]->content, "-n", 2) == 0)
	{
		nl = 0;
		i++;
	}
	while (shell->tokens[i])
	{
		ft_putstr_fd(shell->tokens[i]->content, 1);
		if (shell->tokens[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
}

void	echo(t_shell *shell)
{
	if (shell->tokens[1])
		echo_command(shell);
	else
		ft_putstr_fd("\n", 1);
}
