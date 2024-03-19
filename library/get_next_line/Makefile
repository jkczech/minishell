# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 14:15:09 by jkoupy            #+#    #+#              #
#    Updated: 2024/03/19 15:34:18 by jkoupy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[38;5;196;1m
ORANGE = \033[38;5;208;1m
GREEN = \033[38;5;082;1m
END = \033[0m

NAME = getnextline.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(addprefix object/, $(SRCS:.c=.o))

.SILENCE:

all: $(NAME)

$(NAME): _compiling $(OBJS)
	$(AR) $@ $(OBJS)
	@printf "\r$(GREEN)🚀 ./$(NAME)      created                         \n$(END)"

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE). $(END)";
	@sleep 0.1
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf object/

fclean: clean
	rm -rf $(NAME)

re: fclean all

_compiling:
	@printf "$(ORANGE)🔁 ./$(NAME) \tcompiling$(END)"

.PHONY: all clean fclean re
