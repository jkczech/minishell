# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/05/12 20:16:16 by jseidere         ###   ########.fr        #
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

LIBFT =	library/libft/libft.a
GETNEXTLINE = 	library/get_next_line/getnextline.a

BUILTINS =	builtins/builtins.c \
			builtins/builtins_utils.c \
			builtins/exit.c \
			builtins/exit_util.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/env_utils.c \
			builtins/pwd.c \
			builtins/export.c \
			builtins/export_utils.c \
			builtins/unset.c \
			builtins/cd.c \
			builtins/cd_utils.c

EXECUTOR =	executor/pipex.c \
			executor/pipex_utils.c \
			executor/error.c \
			executor/child.c

EXPANDER =	expander/expander.c \
			expander/expander_utils.c \
			expander/expander_utils2.c
		

INIT =	init/init.c \
		init/init_utils.c

LEXER =	lexer/check_error.c \
		lexer/check_input.c \
		lexer/quotes_handler.c \
		lexer/quotes_handler_utils.c \
		lexer/lexing.c \
		lexer/lexing_utils.c

MAIN = 	main/free.c \
		main/main.c \
		main/shell.c		

PARSER = parser/cmd_utils.c \
		 parser/open_utils.c \
		 parser/parse.c \
 		 parser/tokenizing_utils.c \
		 parser/tokenizing.c

SIGNALS = signals/signals.c

UTILS = utils/general_utils.c \
		utils/tlist.c \
		utils/tlist2.c \
		utils/print.c \
		utils/print2.c \

SRCS =	$(BUILTINS) $(EXECUTOR) $(EXPANDER) $(INIT) $(LEXER) \
        $(MAIN) $(PARSER) $(SIGNALS) $(UTILS)
			
OBJ_DIR = object/
OBJS =  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.d))

all: $(NAME) 

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE). $(END)";
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(NAME): $(LIBFT) $(GETNEXTLINE) $(OBJS) 
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(GETNEXTLINE) -o $(NAME) $(RFLAGS)
	@$(RM) heredocs
	@mkdir heredocs
	@printf "\r$(GREEN)🚀 ./$(NAME)          created                                                                     \n$(END)"

$(LIBFT):
	@make bonus -sC library/libft

$(GETNEXTLINE):
	@printf "$(ORANGE).$(END)"
	@make -sC library/get_next_line

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC library/libft
	@make clean -sC library/get_next_line
	@printf "$(RED)💥 object files\t\tremoved\n$(END)"

fclean: clean cleanf
	@make fclean -sC library/libft
	@make fclean -sC library/get_next_line
	@$(RM) $(NAME)
	@$(RM) test
	@$(RM) heredocs
	@printf "$(RED)💥 ./$(NAME) \t\tremoved\n$(END)"

cleanf:
	@find . -depth -maxdepth 1 -name ".git" -prune -o  -type f ! -name "*.c" ! -name "*.h" ! -name "*.json" ! -name "minishell" ! -name "README.md" ! -name ".gitignore" ! -name Makefile -delete 
	@printf "$(RED)💥 test & useless files removed\n$(END)"

re: _rebuild fclean all

_rebuild:
	@printf "$(ORANGE)🚧 ./$(NAME)\t\trebuild\n$(END)"

nothing:
	@printf "💩$(BROWN) made $(RED)n$(ORANGE)o$(YELLOW)t$(GREEN)h$(BLUE)i$(INDIGO)n$(VIOLET)g\n$(END)"

-include $(DEPS)

.PHONY: all bonus both clean fclean re _rebuild nothing