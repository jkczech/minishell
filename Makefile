# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 12:03:11 by jkoupy            #+#    #+#              #
#    Updated: 2024/02/09 12:21:03 by jkoupy           ###   ########.fr        #
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
DEPFLAGS =-MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d
RM = rm -rf

LIBFT = 	library/libft/build/libft.a
GETNEXTLINE = 	library/get_next_line/build/getnextline.a

MSRCS = main.c
OBJ_DIR = object/
MOBJS =  $(addprefix $(OBJ_DIR), $(MSRCS:.c=.o))
BOBJS = $(addprefix $(OBJ_DIR), $(BSRCS:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(MSRCS:.c=.d))

all: $(LIBFT) $(GETNEXTLINE) $(PIPEX) $(NAME)

object/%.o: source/%.c 
	@mkdir -p $(dir $@)
	@printf "$(ORANGE).$(END)";
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME):	$(LIBFT) $(MOBJS) 
	@$(CC) $(MOBJS) $(CC_FLAGS) $(LIBFT) $(GETNEXTLINE) -o $(NAME)
	@printf "\r$(GREEN)🚀 ./$(NAME)   created              \n$(END)"

$(BNAME): $(LIBFT) $(BOBJS)
	@$(CC) $(BOBJS) $(CC_FLAGS) $(LIBFT) $(GETNEXTLINE) -o $(BNAME)
	@printf "\r$(GREEN)🚀 ./$(BNAME) created                    \n$(END)"

$(LIBFT):
	@printf "$(ORANGE)🔁 ./$(NAME) \t compiling$(END)"
	@make bonus -sC library/libft/build

$(GETNEXTLINE):
	@printf "$(ORANGE).$(END)"
	@make -sC library/get_next_line/build

$(PIPEX):
	@printf "$(ORANGE).$(END)"
	@make -sC library/pipex

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC library/libft/build
	@make clean -sC library/get_next_line/build
	@make clean -sC library/pipex
	@printf "$(RED)💥 object files\t removed\n$(END)"

fclean: clean
	@make fclean -sC library/libft/build
	@make fclean -sC library/get_next_line/build
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