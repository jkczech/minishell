/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:21:00 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/16 03:35:45 by jkoupy           ###   ########.fr       */
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
	else if (check_for(shell->norm_input, "< |", "> |", "| |"))
		error = "syntax error near unexpected token `|'\n";
	else if (check_for(shell->norm_input, "< <", "> <", NULL))
		error = "syntax error near unexpected token `<'\n";
	else if (check_for(shell->norm_input, "< >", "> >", NULL))
		error = "syntax error near unexpected token `>'\n";
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
