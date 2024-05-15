/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/05/15 14:36:39 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////INCLUDES/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

# include "../library/libft/include/libft.h"
# include "../library/get_next_line/include/get_next_line.h"

# include <fcntl.h>		//open, close, read, write
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//perror
# include <string.h>	//strerror
# include <unistd.h>	//access, dup, dup2, execve, exit, fork, pipe, unlink
# include <sys/wait.h>	//wait, waitpid
# include <stdbool.h>	//true, false
# include <errno.h>		//errno
# include <error.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>	//signal
# include <sys/ioctl.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////DEFINES/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

# define WORD 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4
# define PIPE 5

# define PROMPT "MiNiSHell: "
# define ERR_PROMPT "err_shell: "
# define DELIMITER " <>|"
# define SEPARATOR "&|><"
# define FAKE_VAR 2
# define ENV_VAR 1
# define QUESTION_MARK 3
# define DOLLAR_SIGN 4

# define EMPTY 0
# define WRITTEN 1
# define CHILD 2
# define HEREDOC 3

//error messages
# define ERR_ARG_1 	"Error: Wrong number of arguments\n"
# define ERR_ARG_2 	"Error: Not enough arguments\n"
# define EOF_HD "minishell: warning - file delimited by end-of-file (wanted \""

extern int			g_sig;

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
}	t_cmd;

typedef struct s_token
{
	char			*content;
	int				token;
	int				quote;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char	*var;
	char	*value;
	int		flag;
}	t_env;

typedef struct s_quote
{
	char	type;
	bool	in_quotes;
}	t_quote;

typedef struct s_shell
{
	t_list			*env_list;
	char			**envp;
	char			**paths;
	int				exitcode;
	char			*input;
	char			*norm_input;
	int				size;
	t_token			*tokens;
	t_cmd			*cmds;
	int				**pipes;
	int				*child_pids;
	int				hd_i;
	int				mode;
}	t_shell;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////PROTOTYPES///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////BUILTINS///////////////////////////////////////

//builtins.c
bool	copy_envp(t_shell *shell, char **envp);
char	*get_path(t_shell *shell);
bool	is_builtin(t_shell *shell, int i);

//builtins_utils.c
bool	builtin_handler(t_shell *shell, int i);
void	ft_free_list(t_list *list);
long	ft_atol(const char *nptr);

//exit.c
void	exit_shell_status(t_shell *shell, int status);
void	exit_error_msg(char *msg, char *cmd);
void	easy_exit(t_shell *shell, int status);
void	exit_command(t_shell *shell, t_cmd *cmd);

//exit_util.c
bool	check_amount_of_args(char **args);
bool	is_numeric(char *str);
char	*ft_ltoa(long long n);
long	convert_exit_status(t_cmd *cmd);
bool	check_overflow(char *str);

//echo.c
void	print_echo(t_cmd *cmd, int *i, int out);
bool	check_newline(char *str);
void	nnl_echo(t_cmd *cmd, int out);
void	simple_echo(t_cmd *cmd, int out);
void	echo_command(t_shell *shell, t_cmd *cmd, int out);

//env.c
t_env	*ft_fillenv(char *str);
t_list	*ft_envnew_l(void *content);
bool	envp_into_list(char **envp, t_list **env_list);
bool	copy_envp(t_shell *shell, char **envp);
void	env_command(t_shell *shell, t_cmd *cmd, int out);

//env_utils.c
int		check_env_var(char *var);
char	**envp_list_into_char(t_list *env_list);
void	sort_env(t_shell *shell);
char	**handle_empty_env(void);

//pwd.c
void	pwd_command(t_shell *shell, t_cmd *cmd, int out);

//export.c
void	add_env_var(t_shell *shell, char *arg);
void	export_command(t_shell *shell, t_cmd *cmd, int out);
void	export_loop(t_shell *shell, t_cmd *cmd, int *i, bool *swap);
int		strlen_before_char(char *str, char c);
bool	simple_export(t_shell *shell, t_cmd *cmd, int out);

//export_utils.c
bool	is_valid_var(char *var);
void	export_error_minus(t_shell *shell, char c);
void	export_error(t_shell *shell, char *arg);

//unset.c
void	free_env_var(t_env *env);
void	unset_command(t_shell *shell, t_cmd *cmd);
void	delete_env_var(t_shell *shell, char *var);

//cd.c
void	cd_forward(t_shell *shell, char *path);
void	cd_back(t_shell *shell, char *path);
void	cd_home(t_shell *shell);
void	cd_command(t_shell *shell, t_cmd *cmd);
char	*get_env_var(t_shell *shell, char *var);

//cd_utils.c
void	set_env_var(t_shell *shell, char *var, char *value);
void	cd_oldpwd(t_shell *shell);
void	add_oldpwd_to_env(t_shell *shell);
void	add_pwd_to_env(t_shell *shell);
void	update_pwd_n_oldpwd(t_shell *shell);

////////////////////////////////EXECUTOR////////////////////////////////////////

//child.c
void	redirect(t_shell *shell, int input, int output);
void	child(t_shell *shell, int i, int input, int output);

//error.c
void	error_msg(t_shell *shell, char *file);
bool	cmd_not_found(t_shell *shell, int i);
void	cd_error(t_shell *shell, char *path);

//pipex_utils.c
void	copy_pipes(t_shell *shell);
bool	allocate_pids(t_shell *shell);
void	handle_exitcode(t_shell *shell, int i, int status);
void	simple_child(t_shell *shell);

//pipex.c
bool	execute(t_shell *shell);
bool	create_pipes(t_shell *shell);
bool	wait_pids(t_shell *shell);
bool	execute_pipeline(t_shell *shell);
bool	execute_simple(t_shell *shell);

////////////////////////////////EXPANDER////////////////////////////////////////

//expander.c
void	expander(t_shell *shell);
char	*expand_token(t_shell *shell, char *str);
int		q_substr_len(char *str, int i);
void	remove_first_and_last_char(char **str);

//expander_utils.c
char	*expand_vars(t_shell *shell, char *substr, bool last);
bool	expand_exitcode(t_shell *shell, char *substr, int *i, char **res);
void	handle_vars(t_shell *shell, char *substr, int *i, char **res);
bool	is_var(t_shell *shell, char *str);
bool	is_possible_var(char *str);

//expander_utils2.c
int		var_len(char *str);
int		len_until_dollar(char *str, int i);
bool	is_var(t_shell *shell, char *str);
bool	is_possible_var(char *str);
char	*get_env_value(t_shell *shell, char *str);
bool	is_var(t_shell *shell, char *str);
char	*expand_q_substr(t_shell *shell, char *substr, bool last);
char	*copy_until_dollar(char *res, char *substr, int *i);
char	*expand_vars(t_shell *shell, char *substr, bool last);
//////////////////////////////////INIT//////////////////////////////////////////

//init.c
bool	init_shell(t_shell *shell, char **envp);
bool	init_path(t_shell *shell);
bool	init_cmds(t_shell *shell);
void	init_iter(t_shell *shell);
char	**ft_strdup_array(char **array);

//init_utils.c
char	**copy_array(char **arr);
void	print_two_d(char **arr);
void	update_shell_lvl(t_shell *shell);
void	update_shell_(t_shell *shell);

////////////////////////////////LEXER///////////////////////////////////////////

//quotes_handler.c
bool	quotes_checker(char *str);
int		len_w_q(char *str);
char	*remove_quotes(char *str);
void	quote_token(t_shell *shell);

//quotes_handler_utils.c
bool	is_quote(char c);
void	init_variables(int *i, int *len, char *q, bool *q_closed);
void	determine_quote(char *str, int *i, char *q, bool *q_closed);
void	set_quote(char c, t_quote *quote);
void	refresh_quote(char *str, int *i, char *q, bool *q_closed);

//check_input.c
bool	is_sep(char c);
bool	double_sep(char *str, int i);
bool	quotes_checker(char *str);
bool	check_input(t_shell *shell);
bool	check_empty_input(char *str);

//lexing.c
int		count_chars(char *str);
void	process_char_quotes(char *str, char *result, int *i, int *j);
void	process_token(char *str, int *index, int token_type, t_token **head);
void	norm_input(t_shell *shell);

//lexing_utils.c
int		token_count(char *str);
void	token_count_util(char *str, int *i, int *count);

//check_error.c
bool	check_parse_errors(t_shell *shell);
bool	check_for(char *input, char *str1, char *str2, char *str3);
bool	ends_with_redir(char *input);
void	do_error(t_shell *shell, char *error);
bool	compare_strs(char *input, char *str1, char *str2, char *str3);

/////////////////////////////////MAIN///////////////////////////////////////////

//free.c
void	free_cmds(t_shell *shell);
void	free_array(char **array);
bool	free_pipes(t_shell *shell);
void	free_iter(t_shell *shell);
void	free_shell(t_shell *shell);

//main.c
void	argc_check(int argc, char **argv);

//shell.c
void	minishell(t_shell *shell);
bool	read_line(t_shell *shell);

////////////////////////////////PARSER//////////////////////////////////////////

//cmd_utils.c
bool	add_args(t_cmd *cmd, char *arg);
bool	is_command(char *command);
bool	find_command(t_shell *shell, int i);
bool	find_commands(t_shell *shell);
bool	save_command(t_shell *shell, int i, char *command);

//open_utils.c
void	open_input(t_shell *shell, t_cmd *cmd, char *file);
void	open_output(t_shell *shell, t_cmd *cmd, char *file);
void	open_heredoc(t_shell *shell, t_cmd *cmd, char *delimiter, int hd_i);
void	open_append(t_shell *shell, t_cmd *cmd, char *file);
void	heredoc(t_shell *shell, int fd, char *delimiter, bool expand);

//open_utils2.c
void	expand_and_write(t_shell *shell, int fd, char *buf, bool expand);

//parse.c
bool	parse(t_shell *shell);
void	get_tokens(t_shell *shell);
void	get_size(t_shell *shell);
void	get_commands(t_shell *shell);
bool	quote_in_string(char *str);

//tokenizing_utils.c
int		is_delimiter(char c, const char *delim);
int		token_len(char *str, int index, const char *delim);
void	skip_spaces(char *str, int *index);
int		what_token(char *str, int index);
void	add_null_pipe(t_token **head, t_token *token, char *content);

//tokenizing.c
void	process_token(char *str, int *index, int token_type, t_token **head);
char	*allocate_token_content(char *str, int *index);
int		is_delimiter(char c, const char *delim);

///////////////////////////////SIGNALS//////////////////////////////////////////

//signals.c currently in main.c
void	set_signals(t_shell *shell);
void	signal_handler(int signum);
void	heredoc_signal(int status);
void	mode(t_shell *shell, int mode);

////////////////////////////////UTILS///////////////////////////////////////////

//general_utils.c
int		count_args(char **args);
char	*ft_strjoin_free(char *res, char *str);

//tlist.c
t_token	*create_token(char *content, int token);
void	destroy_token(t_token *token);
void	add_token(t_token **head, t_token *new_token);
void	remove_token(t_token **head, t_token *token);
void	free_tokens(t_token *tokens);
int		t_list_size(t_list *list);

//print.c
void	print_tokens(t_token *tokens);
void	print_list(t_token *head);
void	print_env_list(t_list *env_list, int out);
void	print_export_list(t_list *env_list, int out);
void	print_export_var(char *var, char *value, int flag, int out);

//print2.c
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_shell *shell);

#endif
