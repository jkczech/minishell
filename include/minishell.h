/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/22 16:29:50 by jseidere         ###   ########.fr       */
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
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4

# define WORD 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4

//Token

# define WORD 0
# define PIPE 1
# define SEMICOLON 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define AMPERSAND 5
# define HEREDOC 6
# define END 7

typedef struct s_token
{
    char			*content;
    int            token;
    struct s_token	*next;
}				t_token;

//Lexing
void check_input (char *str);
int count_chars(char *str);
int token_count(char *str);
bool ft_is_seperator(char c);
char *norm_input(char *str, int wc, int tc);

//Utils
void print_list(t_token *head);

//Tokenizing
t_token *create_node(char *content);
bool ft_is_word(char *str);
int ft_detect_operator(char c, char d);
char *ft_detect_string(char *str);
t_token *split_and_store(char *input, char *delimiter);

//Free
void ft_free_list(t_token *head);

//cmds.c
bool			init_s_cmds(t_pipex *pipex);
t_simple_cmd	*cmd_new(t_token *token);
void			cmd_add(t_simple_cmd **cmd_table, t_simple_cmd *cmd);
t_simple_cmd	*cmd_last(t_simple_cmd *cmd);


//print.c
void	print_tokens(t_token **tokens);

//dlist.c
t_token *create_token(char *content, int token);
void	destroy_token(t_token *token);
void	free_token_list(t_token **head);
void	add_token(t_token **head, t_token *new_token);


typedef struct s_shell
{
	char			**envp;
	char			*line;
	t_token			**tokens;
	t_list			*history;
	t_pipex			pipex;
}	t_shell;

#endif
