/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:26:27 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 20:32:54 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_and_write(t_shell *shell, int fd, char *buf, bool expand)
{
	char	*tmp;

	if (expand)
		tmp = expand_token(shell, buf);
	else
		tmp = ft_strdup(buf);
	write(fd, tmp, ft_strlen(tmp) - 1);
	write(fd, "\n", 1);
	free(tmp);
}
