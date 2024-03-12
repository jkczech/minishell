/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:44:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/12 15:27:22 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse(t_shell *shell)
{
	get_tokens(shell);
	get_size(shell);
    get_commands(shell);
}

//assigns token types to the tokens
void	get_tokens(t_shell *shell)
{
	t_token	*head;

	head = assign_token_types(shell);
	shell->tokens = &head;
	if (shell->tokens)
		print_tokens(shell->tokens);
}

void	get_size(t_shell *shell)
{
	t_token	*token;
	int		size;

	token = *(shell->tokens);
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
void	get_commands(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = *(shell->tokens);
	if (!token)
		return ;
	shell->cmds = malloc(sizeof(t_cmd) * shell->size);
	i = 0;
	while (i < shell->size)
	{
		shell->cmds[i].args = NULL;
		shell->cmds[i].path = NULL;
		shell->cmds[i].found = false;
		shell->cmds[i].input = -1;
		shell->cmds[i].output = -1;
		i++;
	}
	i = 0;
	while (token)
	{
		if (token->token == PIPE)
			i++;
		else if (token->token == WORD)
			shell->cmds[i].args = token->content;
		else if (token->token == INPUT)
			shell->cmds[i].input = open(token->content, O_RDONLY);
		else if (token->token == OUTPUT)
			shell->cmds[i].output = open(token->content, O_WRONLY | O_CREAT, 0644);
		else if (token->token == HEREDOC)
			shell->cmds[i].input = open(token->content, O_RDONLY);
		else if (token->token == APPEND)
			shell->cmds[i].output = open(token->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
		token = token->next;
	}
}
