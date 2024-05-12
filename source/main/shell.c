/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:46 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/11 18:35:57 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_sig = 0;

void	exit_ctrl_d(t_shell *shell);
//main shell loop, that reads input, checks it and executes it
//TODO: error handling
// MAIN for testing	
void	minishell(t_shell *shell)
{
	char	*line;

	while (true)
	{
		set_signals();
		init_iter(shell);
	/* 	if (!read_line(shell))
			break ; */
		if (isatty(fileno(stdin)))
		{
			shell->input = readline(PROMPT);
			if(!shell->input)
				exit_ctrl_d(shell);
		}
		else
		{
			line = get_next_line(fileno(stdin));
			shell->input = ft_strtrim(line, "\n");
			if (!shell->input)
				break ;
			free(line);
		}
		if (check_input(shell) && parse(shell))
			execute(shell);
		add_history(shell->input);
		free_iter(shell);
	}
}
//exit if ctrl+d
void	exit_ctrl_d(t_shell *shell)
{
		printf("exit\n");
		free_shell(shell);
		exit(shell->exitcode);
}


bool	read_line(t_shell *shell)
{
	shell->input = readline(PROMPT);
	return (shell->input);
}

//signal(SIGTERM, signal_handler);
void	set_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 1;
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 2);
		rl_redisplay();
	}
	else if (signum == SIGTERM)
		printf("Terminated (core dumped)\n");
	else
		printf("Signal %d\n", signum);
}

void	check_g_sig(t_shell *shell)
{
	if (g_sig == 1)
	{
		shell->exitcode = 130;
		g_sig = 0;
	}
	else if (g_sig == 3)
	{
		shell->exitcode = 131;
		g_sig = 0;
	}
	else
		shell->exitcode = 0;
}
