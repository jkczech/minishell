/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:44:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/28 11:48:46 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//parse the input into tokens, then into command table
//TODO: error handling
bool	parse(t_shell *shell)
{
	get_tokens(shell);
	get_size(shell);
	get_commands(shell);
	find_commands(shell);
	return (true);
}

//assigns token types to the tokens
//TODO: malloc into init_shell
//TODO: check if we need ** tokens
void	get_tokens(t_shell *shell)
{
	shell->tokens = malloc(sizeof(t_token *));
	*shell->tokens = assign_token_types(shell);
	if (shell->tokens)
		print_tokens(shell->tokens);
}

//counts the number of commands needed
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
	printf("size: %d\n", shell->size);
}

//creates command table
void	get_commands(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = *(shell->tokens);
	if (!init_cmds(shell))
		return ;
	i = 0;
	while (token && i < shell->size)
	{
		if (token->token == PIPE)
			shell->cmds[++i].args = ft_split(token->content, ' ');
		else if (token->token == WORD)
			add_args(&shell->cmds[i], token->content);
		else if (token->token == INPUT)
			shell->cmds[i].input = open_input(token->content);
		else if (token->token == OUTPUT)
			shell->cmds[i].output = open_output(token->content);
		else if (token->token == HEREDOC)
			shell->cmds[i].input = open_heredoc(token->content);
		else if (token->token == APPEND)
			shell->cmds[i].output = open_append(token->content);
		token = token->next;
	}
	print_cmds(shell);
}
