/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/06 11:06:10 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../library/libft/include/libft.h"
# include "../library/get_next_line/include/get_next_line.h"
# include "../source/executor/pipex.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4
# define PIPE 5

# define PROMPT "🤏🐚: "
# define DELIMITER " <>|"
# define SEPARATOR "&|><'=%"

typedef struct s_shell
{
	char			**envp;
	char			*line;
	t_token			**tokens;
	t_list			*history;
	t_pipex			pipex;
}	t_shell;

//builtins.c
bool	copy_envp(t_shell *shell, char **envp);
char	*get_path(t_shell *shell);
bool	init_shell(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
//void	free_tokens(t_shell *shell);

//cmd_utils.c
bool	init_s_cmds(t_pipex *pipex);
t_s_cmd	*cmd_new(t_token *token);
void	cmd_add(t_s_cmd **cmd_table, t_s_cmd *cmd);
t_s_cmd	*cmd_last(t_s_cmd *cmd);

//dlist.c
t_token	*create_token(char *content, int token);
void	destroy_token(t_token *token);
void	free_token_list(t_token **head);
void	add_token(t_token **head, t_token *new_token);

//lexing_utils.c

//lexing.c
void token_count_util(char *str, int *i, int *count);
int		token_count(char *str);
int		count_chars(char *str);
void	process_token(char *str, int *index, int token_type, t_token **head);
char	*norm_input(char *str, int len);
void	check_input(char *str);

//print.c
void	print_tokens(t_token **tokens);
void	print_list(t_token *head);
void	print_envp(char **envp, char *name);

//tokenizing_utils.c
int		is_delimiter(char c, const char *delim);
int		token_len(char *str, int index, const char *delim);
void	skip_spaces(char *str, int *index);

//tokenizing.c
void	process_token(char *str, int *index, int token_type, t_token **head);
t_token	*assign_token_types(char *str);
int		what_token(char *str, int index);
int		is_delimiter(char c, const char *delim);

//check_input.c
bool	double_sep(char *str, int i);
bool	is_sep(char c);
bool	quotes_checker(char *str);
void	check_input(char *str);

//shell.c
void	envp_into_list(char **envp, t_list *env_list);
void	minishell(char **envp, t_list *env_list);

//lexing_utils_1.c
//are these functions used?
//do they need to be included in the header file?
//these questions were written by Copilot
#endif
