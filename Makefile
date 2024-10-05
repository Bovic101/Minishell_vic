# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 14:24:13 by kdvarako          #+#    #+#              #
#    Updated: 2024/10/05 10:44:36 by vodebunm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_1 = minishell.c
SRC_2 = $(wildcard lex_pars/*.c)
SRC_3 = $(wildcard execute/*.c)
SRC_4 = $(wildcard env/*.c)
SRC_5 = $(wildcard builtins/*.c)
SRC_6 = $(wildcard signals/*.c)
SRC_7 = $(wildcard redirections/*.c)

OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}
OBJ_3 = ${SRC_3:.c=.o}
OBJ_4 = ${SRC_4:.c=.o}
OBJ_5 = ${SRC_5:.c=.o}
OBJ_6 = ${SRC_6:.c=.o}
OBJ_7 = ${SRC_7:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline -lncurses

LIBFT = ./libft/libft.a

all:	${NAME}

${NAME}:	${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5} ${OBJ_6} ${OBJ_7} ${LIBFT}
	${CC} ${CFLAGS} ${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5} ${OBJ_6} ${OBJ_7} ${LIBFT} ${LIBS} -o ${NAME}
	@rm -f ${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5} ${OBJ_6} ${OBJ_7}
	@$(MAKE) clean -C ./libft

${LIBFT}:
	$(MAKE) -C ./libft

clean:
	rm -f ${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5} ${OBJ_6} ${OBJ_7}
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f ${NAME}
	$(MAKE) fclean -C ./libft

re:	fclean all

.PHONY: all clean fclean re
