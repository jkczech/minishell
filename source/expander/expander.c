/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/06 16:03:15 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//finds a variable in the environment
bool	find_variable(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;
	int		i;
	int		len;

	len = ft_strlen(str);
	node = shell->env_list;
	i = 0;
	while (node)
	{
		i = 0;
		var = node->content;
		while (var[i] != '=')
			i++;
		if (ft_strncmp(var, str, i) == 0 && i == len)
			return (true);
		node = node->next;
	}
	return (false);
}

//gets the value of a variable in the environment
char	*get_env_value(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;
	char	*value;
	int		i;
	//char *tmp;

	node = shell->env_list;
/* 	while(*str != '$')
		str++;
	if(*str == '$')
		str++; */
	// Is solving the A="$USER" problem but need on other position
	while (node)
	{
		i = 0;
		var = node->content;
		while (var[i] != '=')
			i++;
		// Find solution if expanding variable is within a string
		if (ft_strncmp(var, str, i) == 0)
		{
			printf("SUCCESS\n");
			value = ft_strdup(var + i + 1);
			if(!value)
				return (NULL);
			return (value);
		}
		node = node->next;
	}
	return (NULL);
}

//transform a string by removing dollar signs & quotes
char	*transform_string(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				result[j++] = str[i++];
		}
		i++;
	}
	str[i] = '\0';
	return (result);
}

//checks if a string is a environment variable
bool	is_expansion(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (find_variable(shell, str + i + 1))
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

void	expander(t_shell *shell)
{
	char	*tmp;
	t_token	*token;
	int		len;

	len = 0;
	token = *shell->tokens;
	while (token)
	{
		tmp = token->content;
		if (is_expansion(shell, tmp))
		{
			while(tmp[len] != '$')
				len++;
			token->content = get_env_value(shell, tmp + len + 1);
			free(tmp);
		}
		token = token->next;
	}
}

//check if $ is followed by a valid variable
//go through tokens and expand variables
//if variable is not found, leave it as is
//if variable is found, replace it with its value
//