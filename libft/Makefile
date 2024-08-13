# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 17:31:46 by kdvarako          #+#    #+#              #
#    Updated: 2024/03/26 15:44:25 by kdvarako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

AR = ar rcs

SRC = ft_isprint.c ft_putendl_fd.c ft_strlcat.c ft_substr.c \
		ft_atoi.c ft_itoa.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c \
		ft_bzero.c	ft_memchr.c	ft_putstr_fd.c	ft_strlen.c	ft_toupper.c \
		ft_calloc.c	ft_memcmp.c ft_split.c ft_strmapi.c \
		ft_isalnum.c ft_memcpy.c ft_strchr.c ft_strncmp.c \
		ft_isalpha.c ft_memmove.c ft_strdup.c ft_strnstr.c \
		ft_isascii.c ft_memset.c ft_striteri.c ft_strrchr.c \
		ft_isdigit.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CC = cc

CFlAGS = -Wall -Wextra -Werror

HEADER = libft.h


all:	${NAME}

${OBJ}: ${SRC}
	${CC} ${CFlAGS} -c ${SRC}

${OBJ_BONUS}: ${SRC_BONUS}
	${CC} ${CFlAGS} -c ${SRC_BONUS}

${NAME}:	${OBJ}
	${AR} ${NAME} ${OBJ}
	ranlib ${NAME}

bonus: ${OBJ} ${OBJ_BONUS}
	${AR} ${NAME} ${OBJ} ${OBJ_BONUS}
	ranlib ${NAME}

clean:
	rm -f ${OBJ} ${OBJ_BONUS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all bonus clean fclean re