/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:44:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/12 12:58:03 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    parse(t_shell *shell)
{
    get_tokens(shell);
	get_size(shell);
    //get_commands(shell);
}

//assigns token types to the tokens
void    get_tokens(t_shell *shell)
{
    t_token *head;
    
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