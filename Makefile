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
#CFLAGS	=	-I. -Wall -Wextra -Werror -O2
CFLAGS	=	-I. -Wall -Wextra -Werror -g3 -c

SRC_DIR	=	srcs

CSRC	=	$(SRC_DIR)/lib.c\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/reaper.c\
			$(SRC_DIR)/exit.c\
			$(SRC_DIR)/parsing.c\
			$(SRC_DIR)/threading.c\
			$(SRC_DIR)/structure.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/action.c
OBJS	=	$(CSRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC)  $(OBJS) -o $@

clean:
	rm -f srcs/*.o

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY = $(NAME) clean fclean re
