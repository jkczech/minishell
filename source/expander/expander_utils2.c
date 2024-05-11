/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:46:33 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/09 15:51:58 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//gets the value of a variable in the environment
char	*get_env_value(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;
	char	*value;

	node = shell->env_list;
	while (node)
	{
		var = ((t_env *)node->content)->var;
		if (ft_strncmp(var, str, ft_strlen(var)) == 0)
		{
			value = ft_strdup(((t_env *)node->content)->value);
			if (!value)
				return (NULL);
			return (value);
		}
		node = node->next;
	}
	return (NULL);
}

//copy skipped characters to the new string until a dollar sign is found
char	*copy_until_dollar(char *res, char *substr, int *i)
{
	int		len;
	char	*tmp;
	char	*tmp2;

	len = len_until_dollar(substr, *i);
	tmp = ft_substr(substr, *i, len);
	tmp2 = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp2, tmp);
	if (!res)
		return (NULL);
	free(tmp2);
	free(tmp);
	*i += len;
	return (res);
}

//strlen before a non alpha character
int	var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '$')
		i++;
	return (i);
}

//strlen before a character
int	len_until_dollar(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		len++;
	}
	return (len);
}
