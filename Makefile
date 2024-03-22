# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/03/22 11:47:34 by jseidere         ###   ########.fr        #
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

BUILTINS =	builtins/builtins.c \
			builtins/builtins_utils.c \
			builtins/exit.c \
			builtins/exit_util.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/pwd.c \

# to be split into different folders
# used to be my pipex
EXECUTOR =	executor/pipex.c \
			executor/error.c \
			executor/free.c \
			executor/here_doc.c \
			executor/parse.c \
			executor/child.c

EXPANDER = expander/expander.c

INIT = init/init.c

LEXER = lexer/lexing.c \
		lexer/check_input.c

MAIN = 	main/main.c \
		main/shell.c
#      main/main_pipex.c
#      main/testing.c			

PARSER = parser/cmd_utils.c \
		 parser/open_utils.c \
		 parser/parse.c \
 		 parser/tokenizing_utils.c \
		 parser/tokenizing.c

SIGNALS = signals/signals.c

UTILS = utils/tlist.c \
		utils/print.c

SRCS =	$(BUILTINS) $(EXECUTOR) $(EXPANDER) $(INIT) $(LEXER) \
        $(MAIN) $(PARSER) $(SIGNALS) $(UTILS)
			
OBJ_DIR = object/
OBJS =  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.d))

TEST_SRCS = testing.c lexing.c tokenizing.c cmd_utils.c dlist.c print.c tokenizing_utils.c
TEST_OBJS = $(addprefix $(OBJ_DIR), $(TEST_SRCS:.c=.o))
TEST_DEPS = $(addprefix $(OBJ_DIR), $(TEST_SRCS:.c=.d))

all: $(LIBFT) $(GETNEXTLINE) $(NAME)

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE). $(END)";
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(NAME):	$(LIBFT) $(OBJS) 
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(GETNEXTLINE) -o $(NAME) $(RFLAGS)
	@printf "\r$(GREEN)🚀 ./$(NAME)   created                                \n$(END)"

#test: $(LIBFT) $(GETNEXTLINE) $(TEST_OBJS)
#	@$(CC) $(TEST_OBJS) $(CFLAGS) $(LIBFT) $(GETNEXTLINE) -o test $(RFLAGS)
#	@printf "\r$(GREEN)🚀 ./test   created			\n$(END)"

$(LIBFT):
	@printf "$(ORANGE)🔁 ./$(NAME) \t compiling$(END)"
	@make bonus -sC library/libft

$(GETNEXTLINE):
	@printf "$(ORANGE).$(END)"
	@make -sC library/get_next_line

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC library/libft
	@make clean -sC library/get_next_line
	@printf "$(RED)💥 object files\t removed\n$(END)"

fclean: clean
	@make fclean -sC library/libft
	@make fclean -sC library/get_next_line
	@$(RM) $(NAME)
	@$(RM) test
	@printf "$(RED)💥 ./$(NAME) \t removed\n$(END)"

re: _rebuild fclean all

_rebuild:
	@printf "$(ORANGE)🚧 ./$(NAME)\t rebuild\n$(END)"

nothing:
	@printf "💩$(BROWN) made $(RED)n$(ORANGE)o$(YELLOW)t$(GREEN)h$(BLUE)i$(INDIGO)n$(VIOLET)g\n$(END)"

-include $(DEPS)

.PHONY: all bonus both clean fclean re _rebuild nothing