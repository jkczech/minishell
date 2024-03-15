/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/15 14:16:39 by jkoupy           ###   ########.fr       */
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
	bool				found; //
	char				*path;
	char				**args;
	int					input;
	int					output;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_token
{
	char			*content;
	int				token;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char			**envp;
	t_list			*env_list;
	char			*input;
	char			*norm_input;
	t_token			**tokens;
	t_list			*history;
	int				size;
	int				infile; //
	int				outfile; //
	t_cmd			*cmds;
	t_cmd			**s_cmds;
	int				**pipes;
	char			**paths;
	int				*child_pids;
	bool			heredoc;
	int				exitcode;
}	t_shell;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////PROTOTYPES///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////BUILTINS///////////////////////////////////////

//builtins.c
bool	init_shell(t_shell *shell, char **envp);
bool	copy_envp(t_shell *shell, char **envp);
char	*get_path(t_shell *shell);
void	handle_commands(t_shell *shell);

//builtins_utils.c
void	free_double_pointer(char **ptr);
void	free_shell(t_shell *shell);
void	free_tokens(t_token **tokens);
void	ft_free_list(t_list *list);

//exit.c
void	exit_shell_status(t_shell *shell, int status);
void	exit_error_msg(t_shell *shell, char *msg, char *cmd, int status);
void	easy_exit(t_shell *shell);
void	exit_command(t_shell *shell);

//exit_util.c
bool	check_amount_of_args(char **args);
bool	is_numeric(char *str);
char	**convert_input(t_shell *shell);

//echo.c
void	echo_command(t_shell *shell);
void	echo(t_shell *shell);

////////////////////////////////EXECUTOR////////////////////////////////////////

//child.c

void	redirect(t_shell shell, int input, int output);
void	children(t_shell shell, int i);
void	child(t_shell shell, int i, int input, int output);

//error.c

void	error_message(char *file);
void	cmd_not_found(t_shell *shell, int i);

//free.c

bool	close_all_fds(t_shell *shell);
bool	free_pipex(t_shell *shell);
bool	free_array(char **array);

//here_doc_bonus.c

void	open_here_doc(t_shell *shell);
void	here_doc(t_shell *shell);

//parse.c

bool	is_command(t_shell *shell, char *command, int i);
void	find_command(t_shell *shell, int i);
void	find_paths(t_shell *shell);
void	open_files(t_shell *shell);
bool	parse_input(t_shell *shell);

//pipex.c

bool	create_pipes(t_shell *shell);
bool	wait_pids(t_shell *shell);
bool	allocate_pids(t_shell *shell);
bool	execute(t_shell *shell);

////////////////////////////////EXPANDER////////////////////////////////////////

//SO FAR M-PTY

//////////////////////////////////INIT//////////////////////////////////////////

//init.c

//so far m-pty

////////////////////////////////LEXER///////////////////////////////////////////

//check_input.c
bool	is_sep(char c);
bool	double_sep(char *str, int i);
bool	quotes_checker(char *str);
bool	check_input(t_shell *shell);
void	del_quotes(char **str);

//lexing.c
void	token_count_util(char *str, int *i, int *count);
int		token_count(t_shell *shell);
int		count_chars(t_shell *shell);
void	process_token(char *str, int *index, int token_type, t_token **head);
void	norm_input(t_shell *shell, int len);

/////////////////////////////////MAIN///////////////////////////////////////////

//shell.c
//void	envp_into_list(char **envp, t_list *env_list);
int		minishell(t_shell *shell);
void	free_iter(t_shell *shell);

////////////////////////////////PARSER//////////////////////////////////////////

//cmd_utils.c
void	init_cmds(t_shell *shell);
void	add_args(t_cmd *cmd, char *arg);
int		count_args(char **args, char **new_args);
void	free_cmds(t_shell *shell);

//open_utils.c
int		open_input(char *file);
int		open_output(char *file);
int		open_heredoc(char *file);
int		open_append(char *file);

//parse.c
void	parse(t_shell *shell);
void	get_tokens(t_shell *shell);
void	get_size(t_shell *shell);
void	get_commands(t_shell *shell);

//tokenizing_utils.c
int		is_delimiter(char c, const char *delim);
int		token_len(char *str, int index, const char *delim);
void	skip_spaces(char *str, int *index);
int		what_token(char *str, int index);

//tokenizing.c
void	process_token(char *str, int *index, int token_type, t_token **head);
t_token	*assign_token_types(t_shell *shell);
int		what_token(char *str, int index);
int		is_delimiter(char c, const char *delim);

////////////////////////////////UTILS///////////////////////////////////////////

//dlist.c
t_token	*create_token(char *content, int token);
void	destroy_token(t_token *token);
void	free_token_list(t_token **head);
void	add_token(t_token **head, t_token *new_token);
void	remove_token(t_token **head, t_token *token);

//print.c
void	print_tokens(t_token **tokens);
void	print_list(t_token *head);
void	print_envp(char **envp, char *name);
void	print_cmds(t_shell *shell);

#endif
