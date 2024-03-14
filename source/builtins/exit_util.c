/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:46:33 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/13 17:27:53 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Checks amount of arguments
bool	check_amount_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (false);
	return (true);
}

//Check if argument is numeric
bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

//Convert input to array
char	**convert_input(t_shell *shell)
{
	char	**result;

	result = ft_split(shell->input, ' ');
	if (!result)
		return (0);
	return (result);
}

/* bool check_exit_code(t_shell *shell, char *args, int i)
{
	
} */