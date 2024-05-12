/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:35:05 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/11 18:57:45 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//copy two dimensional array
char	**copy_array(char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	while (arr[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		if (!ret[i])
		{
			free_array(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

//maybe delete
void	print_two_d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
