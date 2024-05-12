/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:35:37 by jakob             #+#    #+#             */
/*   Updated: 2024/05/12 20:18:03 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//expand variables in a substring (already dealt with quotes)
//finds all variables starting with $ and expands them if they exist
//adds all the skipped characters to the new string
char	*expand_vars(t_shell *shell, char *substr)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (substr && substr[i])
	{
		res = copy_until_dollar(res, substr, &i);
		if (substr[i] == '$' && substr[i + 1] == '?')
		{
			res = ft_strjoin_free(res, ft_itoa(shell->exitcode));
			i += 2;
		}
		else if (substr[i] == '$' && !substr[i + 1])
		{
			res = ft_strjoin_free(res, ft_strdup("$"));
			i++;
		}
		else if (substr[i] == '$')
			handle_vars(shell, substr, &i, &res);
	}
	return (res);
}

//handle the dollar sign
void	handle_vars(t_shell *shell, char *substr, int *i, char **res)
{
	char	*var;
	char	*tmp;

	if (!substr)
		return ;
	var = ft_substr(substr, *i, var_len(substr + *i));
	if (!var)
		return ;
	if (!is_possible_var(var))
		*res = ft_strjoin_free(*res, var);
	else if (is_var(shell, var + 1))
	{
		tmp = ft_strdup(var + 1);
		free(var);
		*res = ft_strjoin_free(*res, get_env_value(shell, tmp));
		free(tmp);
	}
	else if (!is_var(shell, var + 1))
		free(var);
	*i += var_len(substr + *i);
}

//finds a variable in the environment
bool	is_var(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;

	node = shell->env_list;
	while (node)
	{
		var = ((t_env *)node->content)->var;
		if (ft_strncmp(var, str, ft_strlen(str)) == 0)
			return (true);
		node = node->next;
	}
	return (false);
}

//checks if a string is a possible variable
//check if it is expandable
bool	is_possible_var(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '$')
		return (false);
	i++;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
