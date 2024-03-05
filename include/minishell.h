/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/05 14:57:39 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////INCLUDES/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

# include "../library/libft/include/libft.h"
# include "../library/get_next_line/include/get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

//previously in pipex.h
# include <fcntl.h>		//open, close, read, write
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//perror
# include <string.h>	//strerror
# include <unistd.h>	//access, dup, dup2, execve, exit, fork, pipe, unlink
# include <sys/wait.h>	//wait, waitpid
# include <stdbool.h>	//true, false
# include <errno.h>		//errno
# include <error.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////DEFINES/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

# define WORD 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4
# define PIPE 5

# define PROMPT "🤏🐚: "
# define DELIMITER " <>|"
# define SEPARATOR "&|><'=%"

//error messages

# define ERR_ARG_1 	"Error: Wrong number of arguments\n"
# define ERR_ARG_2 	"Error: Not enough arguments\n"
# define ERR_IN 	"Error: infile undefined\n"
# define ERR_OUT	"Error: outfile undefined\n"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////STRUCTS/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct s_cmd
{
	bool	found;
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_simple_cmd
{
	char				*path;
	char				**args;
	int					input;
	int					output;
	struct s_simple_cmd	*next;
}	t_s_cmd;

typedef struct s_token
{
	char			*content;
	int				token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_pipex
{
	int				size;
	int				infile;
	int				outfile;
	t_cmd			*cmds;
	t_s_cmd			**s_cmds;
	int				**pipes;
	char			**paths;
	char			**argv;
	char			**envp;
	int				*child_pids;
	bool			heredoc;
	int				exitcode;
	t_token			**tokens;
}	t_pipex;

typedef struct s_shell
{
	char			**envp;
	char			*line;
	t_token			**tokens;
	t_list			*history;
	t_pipex			pipex;
}	t_shell;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////PROTOTYPES///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////BUILTINS//////////////////////////////////////

//builtins.c
bool	copy_envp(t_shell *shell, char **envp);
char	*get_path(t_shell *shell);
bool	init_shell(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
void	free_tokens(t_shell *shell);

////////////////////////////////EXECUTOR////////////////////////////////////////

//child.c

void	redirect(t_pipex pipex, int input, int output);
void	children(t_pipex pipex, int i);
void	child(t_pipex pipex, int i, int input, int output);

//error.c

void	error_message(char *file);
void	cmd_not_found(t_pipex *pipex, int i);

//free.c

bool	close_all_fds(t_pipex *pipex);
bool	free_pipex(t_pipex *pipex);
bool	free_array(char **array);

//here_doc_bonus.c

void	open_here_doc(t_pipex *pipex);
void	here_doc(t_pipex *pipex);

//parse.c

bool	is_command(t_pipex *pipex, char *command, int i);
void	find_command(t_pipex *pipex, int i);
void	find_paths(t_pipex *pipex);
void	open_files(t_pipex *pipex);
bool	parse_input(t_pipex *pipex);

//pipex.c

bool	create_pipes(t_pipex *pipex);
bool	wait_pids(t_pipex *pipex);
bool	allocate_pids(t_pipex *pipex);
bool	execute(t_pipex *pipex);

////////////////////////////////EXPANDER////////////////////////////////////////

//SO FAR M-PTY

//////////////////////////////////INIT//////////////////////////////////////////

//init.c
bool	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
bool	init_cmds(t_pipex *pipex);

////////////////////////////////LEXER///////////////////////////////////////////

//check_input.c
bool	is_sep(char c);
bool	quotes_checker(char *str);
void	check_input(char *str);

//lexing.c
int		token_count(char *str);
int		count_chars(char *str);
void	process_token(char *str, int *index, int token_type, t_token **head);
char	*norm_input(char *str, int len);
void	check_input(char *str);

/////////////////////////////////MAIN///////////////////////////////////////////

//shell.c
void	envp_into_list(char **envp, t_list *env_list);
void	minishell(char **envp, t_list *env_list);

////////////////////////////////PARSER//////////////////////////////////////////

//cmd_utils.c
bool	init_s_cmds(t_pipex *pipex);
t_s_cmd	*cmd_new(t_token *token);
void	cmd_add(t_s_cmd **cmd_table, t_s_cmd *cmd);
t_s_cmd	*cmd_last(t_s_cmd *cmd);

//tokenizing_utils.c
int		is_delimiter(char c, const char *delim);
int		token_len(char *str, int index, const char *delim);
void	skip_spaces(char *str, int *index);

//tokenizing.c
void	process_token(char *str, int *index, int token_type, t_token **head);
t_token	*assign_token_types(char *str);
int		what_token(char *str, int index);
int		is_delimiter(char c, const char *delim);

////////////////////////////////UTILS///////////////////////////////////////////

//dlist.c
t_token	*create_token(char *content, int token);
void	destroy_token(t_token *token);
void	free_token_list(t_token **head);
void	add_token(t_token **head, t_token *new_token);

//print.c
void	print_tokens(t_token **tokens);
void	print_list(t_token *head);
void	print_envp(char **envp, char *name);

#endif
