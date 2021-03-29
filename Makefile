# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:52:53 by hmickey           #+#    #+#              #
#    Updated: 2021/03/25 16:18:40 by hmickey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INCLUDE		=	

PATH_CONF	=	./src/parse_config/

PATH_LIB	=	../lib/

PATH_SIG	=	srcs/signals/

PATH_TERM	=	srcs/terminal/

PATH_EXECVE	=	src/execve/

PATH_ENV	=	src/env/

PATH_CD		=	src/cd/

PATH_PWD	=	src/pwd/


SRCS		=	main.c\
				${PATH_CD}cd.c\
				${PATH_PWD}pwd.c\
				${PATH_ENV}env.c\
				${PATH_EXECVE}execve.c\

OBJS		= ${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

CFLAGS		= #-Wall -Wextra -Werror 

TERMLIB		=	-ltermcap

.c.o:		
				${CC} -g ${CFLAGS}  -c -I include $< -o ${<:.c=.o}


.PHONY:			all clean fclean re

$(NAME):		${OBJS} ${INCLUDE}
				@${MAKE} -C lib 
				@${CC} ${TERMLIB} lib/libft.a ${OBJS} -o minishell

all:			${NAME}

clean:
				${RM} ${OBJS}
				${MAKE} clean -C lib

fclean:			clean
				${RM} ${NAME} lib/libft.a

-include		${OBJ:.o=.d}

re:				fclean all
