# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/28 01:12:19 by sfournio          #+#    #+#              #
#    Updated: 2020/12/11 02:10:12 by sfournio         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/basic_printers.c \
		srcs/ft_printf.c \
		srcs/checks.c \
		srcs/put_d_i.c \
		srcs/put_u.c \
		srcs/put_c.c \
		srcs/put_s.c \
		srcs/put_x.c \
		srcs/put_p.c \
		srcs/mini_lib.c \
		srcs/utils.c

OBJS = ${SRCS:.c=.o}

HEADERF = includes

HEADER = ft_printf.h

NAME = libftprintf.a

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

%.o:	%.c ${HEADERF}/${HEADER}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I${HEADERF}

$(NAME):	${OBJS}
			ar rc ${NAME} ${OBJS}

all:		${NAME}
			
clean:
			${RM} ${OBJS} ${OBJBONUS}

fclean:		clean
			${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re