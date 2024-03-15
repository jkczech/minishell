/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/03/15 14:32:34 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a character is a separator
bool	is_sep(char c)
{
	int	i;

	i = 0;
	while (SEPARATOR[i])
	{
		if (SEPARATOR[i] == c)
			return (true);
		else
			i++;
	}
	return (false);
}

//checks if a character is a double separator
bool	double_sep(char *str, int i)
{
	if ((str[i] == '|' && str[i + 1] == '|')
		|| (str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		return (true);
	return (false);
}

//checks if amount of quotes is even
bool	quotes_checker(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		return (false);
	return (true);
}

//deletes quotes at the beginning and the end of a str
void	del_quotes(char **str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(*str);
	printf("len: %d\n", len);
	tmp = (char *)malloc(sizeof(char) * (len - 1));
	if (!tmp)
		return ;
	while ((*str)[i + 1])
	{
		tmp[i] = (*str)[i + 1];
		i++;
	}
	tmp[i - 1] = '\0';
	free(*str);
	*str = tmp;
}

//checks the input and saves it in a list of tokens
//if the input is invalid, returns false
bool	check_input(t_shell *shell)
{
	if (!quotes_checker(shell->input))
		return (NULL);
	while (shell->input[0] == '"' && \
		shell->input[ft_strlen(shell->input) - 1] == '"')
	{
		del_quotes(&shell->input);
		if (!shell->input)
			return (false);
	}
	norm_input(shell, token_count(shell) - 1 + count_chars(shell));
	if (!shell->norm_input)
		return (false);
	return (true);
}
