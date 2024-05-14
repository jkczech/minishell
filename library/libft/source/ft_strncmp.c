/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:06:50 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 13:59:05 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i != n)
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	return (0);
}
