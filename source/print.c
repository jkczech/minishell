/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:40 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/24 16:11:58 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//print tokens in colors depending on token type in one line separated by spaces
void	print_tokens(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (token->token == WORD)
			ft_putstr_fd("\033[0;32m", 1);
		else if (token->token == INPUT)
			ft_putstr_fd("\033[0;34m", 1);
		else if (token->token == OUTPUT)
			ft_putstr_fd("\033[0;33m", 1);
		else if (token->token == HEREDOC)
			ft_putstr_fd("\033[0;35m", 1);
		else if (token->token == APPEND)
			ft_putstr_fd("\033[0;36m", 1);
		ft_putstr_fd(token->content, 1);
		ft_putstr_fd("\033[0m", 1);
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
