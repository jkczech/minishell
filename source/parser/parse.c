/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:44:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/12 13:38:56 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//parse the input into tokens, then into command table
//TODO: error handling
bool	parse(t_shell *shell)
{
	get_tokens(shell);
	get_size(shell);
	expander(shell);
	if (!init_cmds(shell))
		return (false);
	get_commands(shell);
	find_commands(shell);
	return (true);
}

//counts the number of commands needed
void	get_size(t_shell *shell)
{
	t_token	*token;
	int		size;

	token = shell->tokens;
	if (!token)
		return ;
	size = 0;
	while (token)
	{
		if (token->token == PIPE)
			size++;
		token = token->next;
	}
	shell->size = size + 1;
}

//creates command table
//TODO: don't split by space
//print_cmds(shell);
void	get_commands(t_shell *shell)
{
	t_token	*token;
	int		i;

	i = 0;
	token = shell->tokens;
	while (token && i < shell->size)
	{
		if (token->token == PIPE)
			shell->cmds[++i].args = ft_split(token->content, ' ');
		else if (token->token == WORD)
			add_args(&shell->cmds[i], token->content);
		else if (token->token == INPUT)
			open_input(shell, &shell->cmds[i], token->content);
		else if (token->token == OUTPUT)
			open_output(shell, &shell->cmds[i], token->content);
		else if (token->token == HEREDOC)
			open_heredoc(shell, &shell->cmds[i], token->content, shell->hd_i++);
		else if (token->token == APPEND)
			open_append(shell, &shell->cmds[i], token->content);
		token = token->next;
	}
}
