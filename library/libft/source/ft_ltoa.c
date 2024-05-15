/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:55:47 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/15 15:13:57 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	int_len(long long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	sign(unsigned long long n, char *str, long *i)
{
	if (n > 9)
	{
		sign(n / 10, str, i);
		sign(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_ltoa(long long n)
{
	char				*str;
	long				i;
	long long			nbr;
	unsigned long long	nbr2;

	nbr = n;
	str = malloc(sizeof(char) * (int_len(nbr) + 1));
	if (str == 0)
		return (0);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr2 = -nbr;
	}
	else
		nbr2 = nbr;
	sign(nbr2, str, &i);
	str[i] = '\0';
	return (str);
}
