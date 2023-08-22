# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/13 16:00:08 by jpauline          #+#    #+#              #
#    Updated: 2023/08/22 14:23:17 by jpauline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pong

SRCS	=	pong_fonc.c

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I minilibx-linux
CFLAGS2 =	-L minilibx-linux -lmlx -lXext -lX11 -lm
RM		=	rm -f



.c.o:
	${CC} ${CFLAGS} ${CFLAGS2}  -c $< -o ${<:.c=.o}

#${NAME}	:	${OBJS}
#	ar rcs ${NAME} ${OBJS}

all		:	${NAME}

$(NAME)	: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${CFLAGS2} -o $(NAME)

clean	:
	${RM} ${OBJS}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
