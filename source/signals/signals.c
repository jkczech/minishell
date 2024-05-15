/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:24 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/15 18:46:35 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		g_sig = 0;

//signal(SIGTERM, signal_handler);
//ctrl+c = SIGINT, ctrl+\ = SIGQUIT, ctrl+d = EOF
void	set_signals(t_shell *shell)
{
	if (shell->mode == EMPTY)
	{
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (shell->mode == WRITTEN)
	{
		signal(SIGINT, &c_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (shell->mode == CHILD)
	{
		signal(SIGINT, &c_signal);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (shell->mode == HEREDOC)
	{
		signal(SIGINT, &heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	c_signal(int status)
{
	if (status == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_sig = 1;
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 1;
	}
}

void	heredoc_signal(int status)
{
	if (status == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sig = 1;
	}
}

void	mode(t_shell *shell, int mode)
{
	shell->mode = mode;
	set_signals(shell);
}
