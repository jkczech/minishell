# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 12:07:05 by jkoupy            #+#    #+#              #
#    Updated: 2024/02/09 15:33:28 by jkoupy           ###   ########.fr        #
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

NAME = pipex.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS =-MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d
AR = ar rcs
RM = rm -rf

LIBFT = 	    ../libft/libft.a

SRCS = free.c parse.c child.c error.c pipex.c here_doc.c
OBJ_DIR = object/
OBJS =  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

object/%.o: source/%.c 
	@mkdir -p $(dir $@)
	@printf "$(ORANGE).$(END)";
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(AR) $@ $(OBJS)
	@printf "\r$(GREEN)🚀 ./$(NAME)     created			\n$(END)"

$(LIBFT):
	@printf "$(ORANGE)🔁 ./$(NAME) \t compiling$(END)"
	@make bonus -sC ../libft

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC ../libft
	@printf "$(RED)💥 object files\t removed\n$(END)"

fclean: clean
	@$(RM) $(NAME) $(BNAME)
	@make fclean -sC ../libft
	@printf "$(RED)💥 ./$(NAME) \t removed\n$(END)"

re: _rebuild fclean all

_rebuild:
	@printf "$(ORANGE)🚧 ./$(NAME)\t rebuild\n$(END)"

-include $(DEPS)

.PHONY: all bonus both clean fclean re _rebuild