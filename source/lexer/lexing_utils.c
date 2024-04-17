/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:11:09 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/17 18:59:43 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//additionnal function for token_count
void	token_count_util(char *str, int *i, int *count)
{
	if (str[*i] != '\0' && !is_sep(str[*i]))
	{
		(*count)++;
		if (is_quote(str[*i]))
			while (!is_quote(str[++(*i)]))
				;
		while (str[*i] != ' ' && str[*i] != '\t'
			&& str[*i] != '\0' && !is_sep(str[*i]))
			(*i)++;
	}
	if (double_sep(str, *i))
		(*i)++;
	if (is_sep(str[*i]))
	{
		(*i)++;
		(*count)++;
	}
}

//counts the number of tokens in a string
int	token_count(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (shell->input[i] != '\0')
	{
		while (shell->input[i] == ' ' || shell->input[i] == '\t')
			i++;
		token_count_util(shell->input, &i, &count);
	}
	return (count);
}
