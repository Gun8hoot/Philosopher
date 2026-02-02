# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 19:59:21 by nclavel           #+#    #+#              #
#    Updated: 2026/01/06 20:03:33 by nclavel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philosophers

CC		=	cc
CFLAGS	=	-I. -Wall -Wextra -Werror -g3 -O3

SRC_DIR	=	srcs
INC_DIR	=	incs

CSRC	=	$(SRC_DIR)/lib.c\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/reaper.c\
			$(SRC_DIR)/parsing.c\
			$(SRC_DIR)/threading.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/action.c
SRCS	=	$(CSRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME):
	$(CC) $(CFLAGS) $(CSRC) -o $@

clean:
	rm -f srcs/*.o

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY = $(NAME) clean fclean re
