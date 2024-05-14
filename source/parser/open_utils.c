/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:58 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 12:34:24 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_input(t_shell *shell, t_cmd *cmd, char *file)
{
	if (cmd->input != STDIN_FILENO && cmd->input != -1)
		close(cmd->input);
	cmd->input = open(file, O_RDONLY);
	if (cmd->input < 0)
		error_msg(shell, file);
}

void	open_output(t_shell *shell, t_cmd *cmd, char *file)
{
	if (cmd->output != STDOUT_FILENO && cmd->output != -1)
		close(cmd->output);
	cmd->output = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->output < 0)
		error_msg(shell, file);
}

void	open_heredoc(t_shell *shell, t_cmd *cmd, char *delimiter, int hd_i)
{
	char	*file;
	char	*tmp;
	bool 	expand;
	char	*exp_del;

	if (cmd->input != STDIN_FILENO && cmd->input != -1)
		close(cmd->input);
	tmp = ft_itoa(hd_i++);
	file = ft_strjoin("heredocs/.heredoc", tmp);
	cmd->input = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->input < 0)
		return (error_msg(shell, file));
	expand = !quote_in_string(delimiter);
	exp_del = expand_token(shell, delimiter);
	heredoc(shell, cmd->input, exp_del, expand);
	free(exp_del);
	close(cmd->input);
	cmd->input = open(file, O_RDONLY);
	if (cmd->input < 0)
		error_msg(shell, file);
	free(file);
	free(tmp);
}

void	open_append(t_shell *shell, t_cmd *cmd, char *file)
{
	if (cmd->output != STDOUT_FILENO && cmd->output != -1)
		close(cmd->output);
	cmd->output = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->output < 0)
		error_msg(shell, file);
}

void	heredoc(t_shell *shell, int fd, char *delimiter, bool expand)
{
	char	*buf;

	mode(shell, HEREDOC);
	while (1)
	{
		write(1, "minishell heredoc> ", 19);
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL || *buf == '\0')
		{
			write(1, "\n", 1);
			write(2, EOF_HD, 60);
			write(2, delimiter, ft_strlen(delimiter));
			write(2, "\")\n", 3);
			break ;
		}
		if (ft_strlen(delimiter) == ft_strlen(buf) - 1 && \
			ft_strncmp(delimiter, buf, ft_strlen(delimiter)) == 0)
			break ;
		if (expand)
			buf = expand_token(shell, buf);
		write(fd, buf, ft_strlen(buf) - 1);
		write(fd, "\n", 1);
		free(buf);
	}
	mode(shell, EMPTY);
	free(buf);
}
