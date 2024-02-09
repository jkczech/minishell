# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 12:03:11 by jkoupy            #+#    #+#              #
#    Updated: 2024/02/09 15:46:26 by jseidere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[38;5;196;1m
ORANGE = \033[38;5;208;1m
YELLOW = \033[38;5;226;1m
GREEN = \033[38;5;082;1m
BLUE = \033[38;5;027;1m
INDIGO = \033[38;5;093;1m
VIOLET = \033[38;5;163;1m
WHITE = \033[38;5;231;1m
BROWN = \033[38;5;137;1m
END = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RFLAGS = -lreadline
DEPFLAGS =-MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d
RM = rm -rf

LIBFT = 	    library/libft/libft.a
GETNEXTLINE = 	library/get_next_line/getnextline.a
PIPEX =         library/pipex/pipex.a

SRCS = main_pipex.c
OBJ_DIR = object/
OBJS =  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.d))

all: $(LIBFT) $(GETNEXTLINE) $(PIPEX) $(NAME)

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE).$(END)";
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(NAME):	$(LIBFT) $(OBJS) 
	@$(CC) $(OBJS) $(CFLAGS) $(PIPEX) $(LIBFT) $(GETNEXTLINE) -o $(NAME) $(RFLAGS)
	@printf "\r$(GREEN)🚀 ./$(NAME)   created			\n$(END)"

$(LIBFT):
	@printf "$(ORANGE)🔁 ./$(NAME) \t compiling$(END)"
	@make bonus -sC library/libft

$(GETNEXTLINE):
	@printf "$(ORANGE).$(END)"
	@make -sC library/get_next_line

$(PIPEX):
	@printf "$(ORANGE).$(END)"
	@make -sC library/pipex

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC library/libft
	@make clean -sC library/get_next_line
	@make clean -sC library/pipex
	@printf "$(RED)💥 object files\t removed\n$(END)"

fclean: clean
	@make fclean -sC library/libft
	@make fclean -sC library/get_next_line
	@make fclean -sC library/pipex
	@$(RM) $(NAME)
	@printf "$(RED)💥 ./$(NAME) \t removed\n$(END)"

re: _rebuild fclean all

_rebuild:
	@printf "$(ORANGE)🚧 ./$(NAME)\t rebuild\n$(END)"

nothing:
	@printf "💩$(BROWN) made $(RED)n$(ORANGE)o$(YELLOW)t$(GREEN)h$(BLUE)i$(INDIGO)n$(VIOLET)g\n$(END)"

-include $(DEPS)

.PHONY: all bonus both clean fclean re _rebuild nothing