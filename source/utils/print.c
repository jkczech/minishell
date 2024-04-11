/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:40 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/11 12:43:14 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//print tokens in colors depending on token type in one line separated by spaces
void	print_tokens(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
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
void	print_env_list(t_list *env_list)
{
	char *var;
	char *value;
	int flag;

	var = NULL;
	value = NULL;
	flag = 0;
	while (env_list)
	{
		var = ((t_env*)env_list->content)->var;
		value = ((t_env*)env_list->content)->value;
		flag = ((t_env*)env_list->content)->flag;
		if(flag == 1)
			printf("%s=%s\n", var, value);
		env_list = env_list->next;
	}
}

//print export_list
void	print_export_list(t_list *env_list)
{
	char *var;
	char *value;
	int flag;

	var = NULL;
	value = NULL;
	flag = 0;
	while (env_list)
	{
		var = ((t_env*)env_list->content)->var;
		value = ((t_env*)env_list->content)->value;
		flag = ((t_env*)env_list->content)->flag;
		if(var[0] == '_')
		{
			env_list = env_list->next;
			continue;
		}
		if(value && (flag == 1))
			printf("declare -x %s=\"%s\"\n", var, value);
		else if (flag == 0)
			printf("declare -x %s\n", var);
		
		env_list = env_list->next;
	}
}

//print cmd list
//index, content, input, output
void	print_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->size)
	{
		printf("\033[1mCommands:\n\033[0mindex: %d\nargs: ", i);
		j = 0;
		if (!shell->cmds[i].args)
			printf("null %c\n", i);
		while (shell->cmds[i].args && shell->cmds[i].args[j])
			printf("\033[0;32m%s+\033[0m ", shell->cmds[i].args[j++]);
		if (!shell->cmds[i].args || !shell->cmds[i].args[0])
			printf("(null)");
		printf("\n");
		if (shell->cmds[i].input == STDIN_FILENO)
			printf("input: %d (STD)\n", shell->cmds[i].input);
		else
			printf("input: %d\n", shell->cmds[i].input);
		if (shell->cmds[i].output == STDOUT_FILENO)
			printf("output: %d (STD)\n", shell->cmds[i].output);
		else
			printf("output: %d\n", shell->cmds[i].output);
		printf("\n");
	}
}
