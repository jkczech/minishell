/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:21:00 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 13:59:54 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_parse_errors(t_shell *shell)
{
	char	*error;

	error = NULL;
	if (ft_strnstr(shell->norm_input, "||", ft_strlen(shell->norm_input)))
		error = "syntax error near unexpected token `||'\n";
	else if (ft_strnstr(shell->norm_input, "&&", ft_strlen(shell->norm_input)))
		error = "syntax error near unexpected token `&&'\n";
	else if (check_for(shell->norm_input, "< |", "> |", "| |")
		|| shell->norm_input[0] == '|')
		error = "syntax error near unexpected token `|'\n";
	else if (check_for(shell->norm_input, "< <", "> <", NULL))
		error = "syntax error near unexpected token `<'\n";
	else if (check_for(shell->norm_input, "< >", "> >", NULL))
		error = "syntax error near unexpected token `>'\n";
	else if (ends_with_redir(shell->norm_input))
		error = "syntax error near unexpected token `newline'\n";
	else if (check_for(shell->norm_input, ">>>", "<<<", "|||"))
		error = "syntax error near unexpected symbol\n";
	else if (check_for(shell->norm_input, ">>|", "<<|", NULL))
		error = "syntax error near unexpected symbol\n";
	if (error)
		do_error(shell, error);
	return (error == NULL);
}
//the NULLS were previously "| >" and "| <" but those are possible

bool	check_for(char *input, char *str1, char *str2, char *str3)
{
	int i;
	t_quote quote;

	i = 0;
	quote.type = 0;
	quote.in_quotes = false;
	while (input[i])
	{
		if (input[i] && is_quote(input[i]) && !quote.in_quotes)
		{
			quote.type = input[i];
			quote.in_quotes = true;
		}
		else if (input[i] && input[i] == quote.type && quote.in_quotes)
		{
			quote.in_quotes = false;
			quote.type = 0;
		}
		if (input[i] && !quote.in_quotes && ft_strlen(input + i) >= 3)
		{
			if (ft_strncmp(input + i, str1, ft_strlen(str1)) == 0 \
				|| ft_strncmp(input + i, str2, ft_strlen(str2)) == 0 \
				|| ft_strncmp(input + i, str3, ft_strlen(str3)) == 0)
				return (true);
		}
		i++;
	}
	return (false);
}

//TODO: pipe opens newline in input - not an error
bool	ends_with_redir(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && (ft_isspace(input[i])))
		i--;
	if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		return (true);
	return (false);
}

void 	do_error(t_shell *shell, char *error)
{
	shell->exitcode = 2;
	ft_putstr_fd("MiNiSHell: syntax error: ", 2);
	ft_putstr_fd(error, 2);
}
