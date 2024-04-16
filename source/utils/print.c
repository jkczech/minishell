/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:40 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/16 05:01:53 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//print tokens in colors depending on token type in one line separated by spaces
void	print_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		if (token->token == WORD)
			ft_putstr_fd("\033[0;32m", 1);
		else if (token->token == INPUT)
			ft_putstr_fd("\033[0;34m", 1);
		else if (token->token == OUTPUT || token->token == APPEND)
			ft_putstr_fd("\033[0;33m", 1);
		else if (token->token == HEREDOC)
			ft_putstr_fd("\033[0;35m", 1);
		else if (token->token == PIPE)
			ft_putstr_fd("\033[0;31m", 1);
		if (token->content)
			ft_putstr_fd(token->content, 1);
		else
			ft_putstr_fd("(null)", 1);
		ft_putstr_fd("\033[0m", 1);
		if (token->next)
			ft_putstr_fd("+", 1);
		token = token->next;
	}
	ft_putstr_fd("\n", 1);
}

//prints a list of tokens
//alternative to print_tokens
void	print_list(t_token *head)
{
	while (head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
}

//print envp variables
void	print_envp(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0)
			printf("%s\n", envp[i]);
		i++;
	}
}

//print env_list
void	print_env_list(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

//print cmd list
//index, content, input, output
void	print_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->size)
	{
		printf("\033[1mCommands:\n\033[0mindex: %d\nargs: ", i);
		j = 0;
		if (!shell->cmds[i].args)
			printf("null %c\n", i);
		while (shell->cmds[i].args && shell->cmds[i].args[j])
			printf("\033[0;32m%s+\033[0m ", shell->cmds[i].args[j++]);
		if (!shell->cmds[i].args || !shell->cmds[i].args[0])
			printf("(null)");
		printf("\n");
		if (shell->cmds[i].input == STDIN_FILENO)
			printf("input: %d (STD)\n", shell->cmds[i].input);
		else
			printf("input: %d\n", shell->cmds[i].input);
		if (shell->cmds[i].output == STDOUT_FILENO)
			printf("output: %d (STD)\n", shell->cmds[i].output);
		else
			printf("output: %d\n", shell->cmds[i].output);
		printf("\n");
	}
}
