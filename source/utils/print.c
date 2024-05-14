/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:40 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/14 20:22:44 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//print tokens in colors depending on token type in one line separated by spaces
void	print_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		if (token->token == WORD)
			ft_putstr_fd("\033[0;32m", 1);
		else if (token->token == INPUT)
			ft_putstr_fd("\033[0;34m", 1);
		else if (token->token == OUTPUT || token->token == APPEND)
			ft_putstr_fd("\033[0;33m", 1);
		else if (token->token == HEREDOC)
			ft_putstr_fd("\033[0;35m", 1);
		else if (token->token == PIPE)
			ft_putstr_fd("\033[0;31m", 1);
		if (token->content)
			ft_putstr_fd(token->content, 1);
		else
			ft_putstr_fd("(null)", 1);
		ft_putstr_fd("\033[0m", 1);
		if (token->next)
			ft_putstr_fd("+", 1);
		token = token->next;
	}
	ft_putstr_fd("\n", 1);
}

//prints a list of tokens
//alternative to print_tokens
void	print_list(t_token *head)
{
	while (head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
}

//print env_list
void	print_env_list(t_list *env_list, int out)
{
	char	*var;
	char	*value;
	int		flag;

	var = NULL;
	value = NULL;
	flag = 0;
	while (env_list)
	{
		var = ((t_env *)env_list->content)->var;
		value = ((t_env *)env_list->content)->value;
		flag = ((t_env *)env_list->content)->flag;
		if (flag == 1)
		{
			ft_putstr_fd(var, out);
			ft_putstr_fd("=", out);
			ft_putstr_fd(value, out);
			ft_putstr_fd("\n", out);
		}
		env_list = env_list->next;
	}
}

//print export_list
void	print_export_list(t_list *env_list, int out)
{
	char	*var;
	char	*value;
	int		flag;

	var = NULL;
	value = NULL;
	flag = 0;
	while (env_list)
	{
		var = ((t_env *)env_list->content)->var;
		value = ((t_env *)env_list->content)->value;
		flag = ((t_env *)env_list->content)->flag;
		if (var[0] == '_')
		{
			env_list = env_list->next;
			continue ;
		}
		print_export_var(var, value, flag, out);
		env_list = env_list->next;
	}
}

void	print_export_var(char *var, char *value, int flag, int out)
{
	if (var[0] == '_')
		return ;
	if (flag == 1)
	{
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(var, out);
		ft_putstr_fd("=\"", out);
		ft_putstr_fd(value, out);
		ft_putstr_fd("\"\n", out);
	}
	else if (flag == 0)
	{
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(var, out);
		ft_putstr_fd("\n", out);
	}
}
