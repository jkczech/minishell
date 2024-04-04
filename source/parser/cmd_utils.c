/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/04 13:09:59 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//adds an argument to the args table
void	add_args(t_cmd *cmd, char *arg)
{
	int		i;
	char	**res;

	if (cmd->args == NULL)
	{
		cmd->args = (char **)malloc(sizeof(char *) * 2);
		cmd->args[0] = ft_strdup(arg);
		cmd->args[1] = NULL;
		return ;
	}
	printf("argcount: %d\n", count_args(cmd->args) + 1);
	res = malloc(sizeof(char *) * (count_args(cmd->args) + 2));
	if (!res)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		res[i] = cmd->args[i];
		i++;
	}
	res[i++] = ft_strdup(arg);
	res[i] = NULL;
	free(cmd->args);
	cmd->args = res;
}

// {
// 	int		i;
// 	int		j;
// 	char	**res;

// 	printf("arg = %s\n", arg);
// 	if (cmd->args == NULL)
// 	{
// 		cmd->args = malloc(sizeof(char *) * 2);
// 		cmd->args = &arg;
// 		printf("cmd->args[0] = %s\n", cmd->args[0]);
// 		cmd->args[1] = NULL;
// 		return ;
// 	}
// 	//new_args = ft_split(arg, ' ');
// 	//printf("new_args[0] = %s\n", new_args[0]);
// 	printf("argcount: %d\n", count_args(cmd->args) + 1);
// 	res = malloc(sizeof(char *) * (count_args(cmd->args) + 1));
// 	if (!res)
// 		return ;
// 	i = 0; //?
// 	j = 0; //?
// 	while (cmd->args[i]) // Taking already existing arguments from cmd->args
// 	{
// 		res[j] = cmd->args[i];
// 		printf("res[%d] = %s\n", j, res[j]);
// 		printf("cmd->args[%d] = %s\n", i, cmd->args[i]);
// 		i++;
// 		j++;
// 	}
// 	res[j] = arg;
// 	printf("res[%d] = %s\n", i, res[i]);
// 	res[++j] = NULL;
// 	//free(new_args);
// 	free(cmd->args);
// 	//i = 0;
// 	/* while (res[i])
// 	{
// 		printf("res[%d] = %s\n", i, res[i]);
// 		i++;
// 	} */
// 	cmd->args = res;
// }

//counts the number of arguments for the args table
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
