/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/03 13:29:04 by jkoupy           ###   ########.fr       */
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
# include <limits.h>

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
# define SEPARATOR "&|><'%"

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
	char				*path;
	char				**args;
	int					input;
	int					output;
	struct s_cmd		*next;
	bool				heredoc;
}	t_cmd;

typedef struct s_token
{
	char			*content;
	int				token;
	struct s_token	*next;
	int				quotes;
}	t_token;

typedef struct s_shell
{
	t_list			*env_list;
	t_list			*history;
	char			**envp;
	char			**paths;
	int				exitcode;
	char			*input;
	char			*norm_input;
	int				size;
	t_token			**tokens;
	t_cmd			*cmds;
	int				**pipes;
	int				*child_pids;
	int				hd_i;
}	t_shell;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////PROTOTYPES///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////BUILTINS///////////////////////////////////////

//builtins.c

bool	copy_envp(t_shell *shell, char **envp);
char	*get_path(t_shell *shell);
int		args_counter(char **args);
bool	is_builtin(t_shell *shell, int i);

//builtins_utils.c

bool	builtin_handler(t_shell *shell, t_cmd *cmd);
void	free_shell(t_shell *shell);
void	free_tokens(t_token **tokens);
void	ft_free_list(t_list *list);
long	ft_atol(const char *nptr);

//exit.c

void	exit_shell_status(t_shell *shell, int status);
void	exit_error_msg(t_shell *shell, char *msg, char *cmd, int status);
void	easy_exit(t_shell *shell, int status);
void	exit_command(t_shell *shell, t_cmd *cmd);

//exit_util.c

bool	check_amount_of_args(char **args);
bool	is_numeric(char *str);
char	*ft_ltoa(long n);
long	convert_exit_status(t_cmd *cmd);
bool	check_overflow(char *str);

//echo.c

void	echo_command(t_shell *shell, t_cmd *cmd);

//env.c

t_list	*ft_envnew_l(void *content);
void	env_command(t_shell *shell, t_cmd *cmd);
bool	envp_into_list(char **envp, t_list **env_list);

//env_utils.c

//pwd.c

void	pwd_command(t_shell *shell, t_cmd *cmd);

//export.c

bool	check_valid_arg(char *arg);
void	add_env_var(t_shell *shell, char *arg);
void	export_command(t_shell *shell, t_cmd *cmd);

////////////////////////////////EXECUTOR////////////////////////////////////////

//child.c

void	redirect(t_shell shell, int input, int output);
void	children(t_shell shell, int i);
void	child(t_shell shell, int i, int input, int output);

//error.c

void	error_msg(char *file);
void	cmd_not_found(t_shell *shell, int i);

//pipex.c

bool	create_pipes(t_shell *shell);
bool	wait_pids(t_shell *shell);
bool	allocate_pids(t_shell *shell);
bool	execute_pipeline(t_shell *shell);
bool	execute_simple(t_shell *shell);

////////////////////////////////EXPANDER////////////////////////////////////////

//SO FAR M-PTY

//////////////////////////////////INIT//////////////////////////////////////////

//init.c
bool	init_shell(t_shell *shell, char **envp);
bool	init_path(t_shell *shell);
bool	init_cmds(t_shell *shell);

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

//free.c
void	free_cmds(t_shell *shell);
void	free_array(char **array);
bool	free_pipes(t_shell *shell);
void	free_iter(t_shell *shell);
void	free_shell(t_shell *shell);

//shell.c
//void	envp_into_list(char **envp, t_list *env_list);
int		minishell(t_shell *shell);

////////////////////////////////PARSER//////////////////////////////////////////

//cmd_utils.c
void	add_args(t_cmd *cmd, char *arg);
int		count_args(char **args, char **new_args);
bool	is_command(t_shell *shell, char *command, int i);
void	find_command(t_shell *shell, int i);
bool	find_commands(t_shell *shell);

//open_utils.c
void	open_input(t_cmd *cmd, char *file);
void	open_output(t_cmd *cmd, char *file);
void	open_heredoc(t_cmd *cmd, char *delimiter, int hd_i);
void	open_append(t_cmd *cmd, char *file);
void	heredoc(int fd, char *delimiter);

//parse.c
bool	parse(t_shell *shell);
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

//tlist.c
t_token	*create_token(char *content, int token);
void	destroy_token(t_token *token);
void	add_token(t_token **head, t_token *new_token);
void	remove_token(t_token **head, t_token *token);
void	free_tokens(t_token **tokens);

//print.c
void	print_tokens(t_token **tokens);
void	print_list(t_token *head);
void	print_envp(char **envp, char *name);
void	print_cmds(t_shell *shell);
void	print_env_list(t_list *env_list);

#endif
