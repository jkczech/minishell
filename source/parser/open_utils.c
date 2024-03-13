/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/13 14:40:31 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	open_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	open_heredoc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	open_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	return (fd);
}
