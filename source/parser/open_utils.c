/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/02 20:17:36 by jkoupy           ###   ########.fr       */
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

int	open_heredoc(char *delimiter, int hd_i)
{
	char	*file;
	int		fd;

	file = ft_strjoin("heredocs/.heredoc", ft_itoa(++hd_i));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	heredoc(fd, delimiter);
	close(fd);
	fd = open(file, O_RDONLY);
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

void	heredoc(int fd, char *delimiter)
{
	char	*buf;

	while (1)
	{
		write(1, "minishell heredoc> ", 19);
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL || *buf == '\0')
		{
			write(1, "\n", 1);
			write(2, "minishell: warning - file delimited by end-of-file ", 51);
			write(2, "(wanted \"", 9);
			write(2, delimiter, ft_strlen(delimiter));
			write(2, "\")\n", 3);
			break ;
		}
		if (ft_strlen(delimiter) == ft_strlen(buf) - 1 && \
			ft_strncmp(delimiter, buf, ft_strlen(delimiter)) == 0)
			break ;
		write(fd, buf, ft_strlen(buf) - 1);
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
}
