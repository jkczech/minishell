/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:40 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/22 15:11:38 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*# define WORD 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4*/

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
		ft_putstr_fd(" ", 1);
		token = token->next;
	}
	ft_putstr_fd("\n", 1);
}
