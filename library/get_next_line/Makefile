# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 14:15:09 by jkoupy            #+#    #+#              #
#    Updated: 2024/02/09 15:36:20 by jkoupy           ###   ########.fr        #
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

NAME = getnextline.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(addprefix object/, $(SRCS:.c=.o))

.SILENCE:

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $?
	@printf "\r$(GREEN)🚀 ./$(NAME) created                         \n$(END)"

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE).$(END)";
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf object/

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
