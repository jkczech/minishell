/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:18:03 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/09 14:33:58 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//count the number of arguments
int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

//joins strings and reallocates memory while freeing the old string
char	*ft_strjoin_free(char *res, char *str)
{
	char	*tmp;

	if (!res)
		return (str);
	tmp = ft_strdup(res);
	if (!tmp)
		return (NULL);
	free(res);
	if (!str)
		return (tmp);
	res = ft_strjoin(tmp, str);
	if (!res)
		return (NULL);
	free(tmp);
	free(str);
	return (res);
}
