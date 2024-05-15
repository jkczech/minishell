/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:35:37 by jakob             #+#    #+#             */
/*   Updated: 2024/05/15 21:23:30 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//expand variables in a substring (already dealt with quotes)
//finds all variables starting with $ and expands them if they exist
//adds all the skipped characters to the new string
char	*expand_vars(t_shell *shell, char *substr, bool last)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (substr && substr[i])
	{
		if (ft_strlen(substr) == 3 && substr[0] == '"'
			&& substr[1] == '$' && substr[2] == '"')
		{
			res = ft_strjoin_free(res, ft_strdup("$"));
			break ;
		}
		res = copy_until_dollar(res, substr, &i);
		if (expand_exitcode(shell, substr, &i, &res))
			continue ;
		else if (substr[i] == '$' && !substr[i + 1] && last)
		{
			res = ft_strjoin_free(res, ft_strdup("$"));
			i++;
		}
		else if (substr[i] == '$')
			handle_vars(shell, substr, &i, &res);
	}
	return (res);
}

bool	expand_exitcode(t_shell *shell, char *substr, int *i, char **res)
{
	if (substr[*i] == '$' && substr[*i + 1] == '?')
	{
		*res = ft_strjoin_free(*res, ft_itoa(shell->exitcode));
		*i += 2;
		return (true);
	}
	return (false);
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
	{
		if (ft_strlen(var) > 1)
			*res = ft_strjoin_free(*res, var);
	}
	else if (!is_possible_var(var) && ft_strlen(var) == 1)
		*res = ft_strjoin_free(*res, "$");
	else if (is_var(shell, var + 1))
	{
		tmp = ft_strdup(var + 1);
		*res = ft_strjoin_free(*res, get_env_value(shell, tmp));
		free(tmp);
	}
	*i += var_len(substr + *i);
	if (var)
		free(var);
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
		if (ft_strncmp(var, str, ft_strlen(str) + 1) == 0)
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
	if (!ft_isalnum(str[i]) && str[i] != '_')
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
