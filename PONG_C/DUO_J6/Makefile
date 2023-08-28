# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:42:32 by mde-la-s          #+#    #+#              #
#    Updated: 2022/02/23 19:33:08 by jpauline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

LIBFT	=	libft/libft.a
SRCS	=	main.c parsing.c init_va.c parse_data.c \
			parse_map.c parse_map2.c clean_exit.c \
			engine.c key_move.c cast_rays.c walldist.c \
			draw_map.c

CC		=	gcc
CFLAGS  =	-Wall -Wextra -Werror -I minilibx-linux
CFLAGS2 =	-L minilibx-linux -lmlx -lXext -lX11 -lm
OBJS	=	${SRCS:.c=.o}
DEP 	=	$(OBJS:.o=.d)

all		:	libft mlx ${NAME}

$(NAME)	:	$(OBJS)
		${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT} ${CFLAGS2}

libft	:
		@make -C libft

mlx		:
		@make -C minilibx-linux

-include	:	$(DEP)

%.o:%.c
		$(CC) -MMD $(CFLAGS) -c $< -o $@

clean	:
		@make -C ./libft clean
		@make -C ./minilibx-linux clean
		rm -f ${DEP}
		rm -f ${OBJS}

fclean	:
		@make -C ./libft fclean
		@make -C ./minilibx-linux clean
		rm -f ${DEP}
		rm -f ${OBJS}
		rm -f ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re libft mlx
