# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 14:24:13 by kdvarako          #+#    #+#              #
#    Updated: 2024/08/08 12:20:29 by kdvarako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_1 = minishell.c
SRC_2 = $(wildcard lex_pars/*.c)
SRC_3 = $(wildcard execute/*.c)
SRC_4 = $(wildcard env/*.c)
SRC_5 = $(wildcard history/*.c)

OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}
OBJ_3 = ${SRC_3:.c=.o}
OBJ_4 = ${SRC_4:.c=.o}
OBJ_5 = ${SRC_5:.c=.o}

CC = cc

CFlAGS = -Wall -Wextra -Werror -lreadline

LIBFT = ./libft/libft.a

all:	${NAME}

.c.o:
	${CC} -c $< -o ${<:.c=.o}

$(LIBFT):
	$(MAKE) -C ./libft

${NAME}:	${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5} ${LIBFT}
	${CC} ${CFlAGS} ${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5} ${LIBFT} -o ${NAME}

clean:
	rm -f ${OBJ_1} ${OBJ_2} ${OBJ_3} ${OBJ_4} ${OBJ_5}
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f ${NAME}
	$(MAKE) fclean -C ./libft

re:	fclean all

.PHONY: all clean fclean re