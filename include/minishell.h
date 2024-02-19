/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:04:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/02/19 12:35:56 by jseidere         ###   ########.fr       */
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

//Token

# define WORD 0
# define PIPE 1
# define SEMICOLON 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define APPEND 5
# define HEREDOC 6
# define END 7

typedef struct s_lst
{
    char			*content;
    int            token;
    struct s_lst	*next;
}				t_lst;

void check_input (char *str);

#endif