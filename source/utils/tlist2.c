/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:24:33 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/12 15:24:49 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int t_list_size(t_list *list)
{
    int		i;
    t_list	*tmp;

    i = 0;
    tmp = list;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}
