/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/26 13:34:11 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//adds an argument to the args table
void	add_args(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**res;
	char	**new_args;

	if (cmd->args == NULL)
	{
		cmd->args = ft_split(arg, ' ');
		return ;
	}
	new_args = ft_split(arg, ' ');
	res = malloc(sizeof(char *) * (count_args(cmd->args, new_args) + 1));
	if (!res)
		return ;
	i = -1;
	while (cmd->args[++i])
		res[i] = cmd->args[i];
	j = 0;
	while (new_args[j])
		res[i++] = new_args[j++];
	res[i] = NULL;
	free(new_args);
	free(cmd->args);
	cmd->args = res;
}

//counts the number of arguments for the args table
int	count_args(char **args, char **new_args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
		i++;
	j = 0;
	while (new_args[j])
		j++;
	return (i + j);
}
