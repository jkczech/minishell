/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/09 15:01:11 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//strlen before a non alpha character
int strlen_b_sc(char *str)
{
	int i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

//strlen before a character
int strlen_before_a(char *str)
{
	int i;

	i = 0;
	while (str[i] && !ft_isalpha(str[i]) && str[i] != '$')
		i++;
	return (i);
}

//expand variables
char *expand(t_shell *shell, char *str)
{
	char *value;

	value = get_env_value(shell, str);

	return (value);
}

//finds a variable in the environment
bool	find_var(t_shell *shell, char *str)
{
	t_list	*node;
	char	*var;
	int		i;
	int		len;

	len = strlen_b_sc(str);
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

	node = shell->env_list;
	while (node)
	{
		i = 0;
		var = node->content;
		while (var[i] != '=')
			i++;
		if (ft_strncmp(var, str, i) == 0)
		{
			value = ft_strdup(var + i + 1);
			if(!value)
				return (NULL);
			return (value);
		}
		node = node->next;
	}
	return (NULL);
}

//checks if a string is a environment variable
bool	is_var(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (find_var(shell, str + i + 1))
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

//checks if a string is a fake environment variable
bool is_fake_var(t_shell *shell, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!find_var(shell, str + i + 1))
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

char *convert_str(t_shell *shell, char *str)
{
	char *substr;
	char *new_str;
	int len;
	int i;

	i = 0;
	len = 0;
	new_str = ft_strdup("");
	if(!new_str)
		return (NULL);
	while(str[i])
	{
		if(ft_isalnum(str[i]) || str[i] == '$')
			len = strlen_b_sc(str + i);
		else
			len = strlen_before_a(str + i);
		substr = ft_substr(str, i, len);
		if(!substr)
			return (NULL);
		if(is_var(shell, substr))
			substr = expand(shell, substr + 1);
		else if(is_fake_var(shell, substr))
			substr = ft_strdup("");
		if(!substr)
			return (NULL);
		new_str = ft_strjoin(new_str, substr);
		if(!new_str)
			return (NULL);
		free(substr);
		i += len;
	}
	return (new_str);
}

//expands variables in the tokens
void	expander(t_shell *shell)
{
	char	*tmp;
	t_token	*token;
	//int		len;
	//char	*value;
	char	*var;

	token = *shell->tokens;
	while (token)
	{
		tmp = token->content;
		var = convert_str(shell, tmp);
		free(tmp);
		token->content = ft_strdup(var);
		free(var);
		token = token->next;
	}
}


//check if $ is followed by a valid variable
//go through tokens and expand variables
//if variable is not found, leave it as is
//if variable is found, replace it with its value
//