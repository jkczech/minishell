/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:27:19 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/20 14:46:13 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/include/libft.h"
# include "../../get_next_line/include/get_next_line.h"

# include <fcntl.h>		//open, close, read, write
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//perror
# include <string.h>	//strerror
# include <unistd.h>	//access, dup, dup2, execve, exit, fork, pipe, unlink
# include <sys/wait.h>	//wait, waitpid
# include <stdbool.h>	//true, false
# include <errno.h>		//errno
# include <error.h>

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
	struct s_simple_cmd	*next;
}	t_simple_cmd;

typedef struct s_token
{
	char			*content;
	int				token;
	struct s_token	*next;
}	t_token;

typedef struct s_pipex
{
	int				size;
	int				infile;
	int				outfile;
	t_cmd			*cmds;
	t_simple_cmd	**s_cmds;
	int				**pipes;
	char			**paths;
	char			**argv;
	char			**envp;
	int				*child_pids;
	bool			heredoc;
	int				exitcode;
	t_token			**tokens;
}	t_pipex;

//error messages

# define ERR_ARG_1 	"Error: Wrong number of arguments\n"
# define ERR_ARG_2 	"Error: Not enough arguments\n"
# define ERR_IN 	"Error: infile undefined\n"
# define ERR_OUT	"Error: outfile undefined\n"

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

//main.c or main_bonus.c

bool	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
bool	init_cmds(t_pipex *pipex);

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

#endif
