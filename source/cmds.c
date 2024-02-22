/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:55:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/22 13:49:05 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
typedef struct s_simple_cmd
{
	int			allocated;
	int			argc;
	char		*path;
	char		**args;
	s_simple_cmd *next;
}	t_simple_cmd;
*/

//help pipex init
//allocate memory for simple commands table

bool	init_s_cmds(t_pipex *pipex)
{
	t_simple_cmd	*temp;
	t_token			*token;

	if (!pipex->tokens)
		return (false);
	token = *pipex->tokens;
	*pipex->s_cmds = NULL;
	while (token)
	{
		if (token->token == WORD)
		{
			temp = cmd_new(token);
			cmd_add(pipex->s_cmds, temp);
		}
		token = token->next;
	}
	if (!pipex->s_cmds || !*pipex->s_cmds)
		return (false);
	return (true);
}

t_simple_cmd	*cmd_new(t_token *token)
{
	t_simple_cmd	*cmd;

	if (!token)
		return (NULL);
	cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split(token->content, ' ');
	if (token->prev && token->prev->token == INPUT)
		cmd->input = open(token->prev->content, O_RDONLY);
	else
		cmd->input = -1;
	if (token->next && token->next->token == OUTPUT)
		cmd->output = open(token->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->next && token->next->token == APPEND)
		cmd->output = open(token->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->output = -1;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add(t_simple_cmd **cmd_table, t_simple_cmd *cmd)
{
	t_simple_cmd	*temp;

	if (!cmd_table || !cmd)
		return ;
	if (!*cmd_table)
	{
		*cmd_table = cmd;
		return ;
	}
	temp = cmd_last(*cmd_table);
	if (temp)
		temp->next = cmd;
}

t_simple_cmd	*cmd_last(t_simple_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
