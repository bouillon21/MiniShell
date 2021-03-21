# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:52:53 by hmickey           #+#    #+#              #
#    Updated: 2021/03/21 14:26:06 by cshelli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	сub3D

INCLUDE		=	

PATH_CONF	=	./src/parse_config/

PATH_GNL	=	../lib/

SRCS		=	test.c\
				${PATH_GNL}get_next_line.c\
				${PATH_GNL}get_next_line_utils.c\

OBJS		= ${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

CFLAGS		= #-Wall -Wextra -Werror 

.c.o:		
				${CC} -g ${CFLAGS}  -c -I./../include/ $< -o ${<:.c=.o}


.PHONY:			all clean fclean re

$(NAME):		${OBJS} ${INCLUDE}
				@${MAKE} -C ../lib 
				@${CC} ../lib/libft.a ${OBJS} -o minishell

all:			${NAME}

clean:
				${RM} ${OBJS}
				${MAKE} clean -C ../lib

fclean:			clean
				${RM} ${NAME} ../lib/libft.a

-include		${OBJ:.o=.d}

re:				fclean all
