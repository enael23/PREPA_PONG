# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/26 15:31:23 by mde-la-s          #+#    #+#              #
#    Updated: 2022/02/15 16:40:24 by mde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c \
		alloc_with.c \
		get_next_line.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_charthere.c \
		ft_delchar.c \
		ft_duptab.c \
		ft_freesplit.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isint.c \
		ft_isnum.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_strisdigit.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strthere.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c

OBJS	=	${SRCS:.c=.o}

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

all	:	 ${NAME}

$(NAME)	: ${OBJS}
	${CC} ${CFLAGS} -c ${SRCS}
	ar rcs ${NAME} ${OBJS}

clean	:
	rm -f ${OBJS}

fclean	: clean
	rm -f ${NAME}

re		: fclean all

.PHONY : all clean fclean re
