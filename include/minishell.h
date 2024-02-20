/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/20 14:46:07 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../library/libft/include/libft.h"
# include "../library/get_next_line/include/get_next_line.h"
# include "../library/pipex/include/pipex.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 0

/* typedef struct s_list
{
    char			*content;
    struct s_list	*next;
}				t_list; */

//cmds.c
bool			init_s_cmds(t_pipex *pipex);
t_simple_cmd	*cmd_new(t_token *token);
void			cmd_add(t_simple_cmd **cmd_table, t_simple_cmd *cmd);
t_simple_cmd	*cmd_last(t_simple_cmd *cmd);

#endif