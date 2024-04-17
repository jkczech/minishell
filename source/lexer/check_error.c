/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:21:00 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/17 22:39:23 by jkoupy           ###   ########.fr       */
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
	if (error)
	{
		ft_putstr_fd(ERR_PROMPT, STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		shell->exitcode = 2;
		return (false);
	}
	return (true);
}
//the NULLS were previously "| >" and "| <" but those are possible

bool	check_for(char *input, char *str1, char *str2, char *str3)
{
	if (ft_strnstr(input, str1, ft_strlen(input))
		|| ft_strnstr(input, str2, ft_strlen(input))
		|| ft_strnstr(input, str3, ft_strlen(input)))
		return (true);
	return (false);
}

//TODO: pipe opens newline in input - not an error
bool	ends_with_redir(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i--;
	if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		return (true);
	return (false);
}
