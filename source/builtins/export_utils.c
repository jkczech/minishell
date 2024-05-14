/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:48:04 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/13 16:38:42 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// checks if variable is valid
bool	is_valid_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// checks if variable is valid
void	export_error_minus(t_shell *shell, char c)
{
	shell->exitcode = 2;
	ft_putstr_fd("MiNiSHell: export: `-", 2);
	ft_putstr_fd(&c, 2);
	ft_putstr_fd("\': invalid option\n", 2);
	ft_putstr_fd("export: usage: export name[=value] ... or export -p\n", 2);
}

void	export_error(t_shell *shell, char *arg)
{
	shell->exitcode = 1;
	ft_putstr_fd("MiNiSHell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}
