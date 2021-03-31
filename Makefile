# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:52:53 by hmickey           #+#    #+#              #
#    Updated: 2021/03/31 19:46:42 by hmickey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	сub3D

INCLUDE		=	

PATH_CONF	=	./src/parse_config/

PATH_LIB	=	./lib/

PATH_SIG	=	src/signals/

PATH_TERM	=	src/terminal/

PATH_PARSE	=	src/parsing/

PATH_LISTS	=	src/lists/

SRCS		=	main.c\
				${PATH_LIB}get_next_line.c\
				${PATH_LIB}get_next_line_utils.c\
				${PATH_SIG}signal.c \
				${PATH_TERM}terminal.c\
				${PATH_TERM}secondary_functions.c\
				${PATH_TERM}key_functions.c\
				${PATH_TERM}key_functions2.c\
				${PATH_TERM}del_bs_functions.c\
				${PATH_PARSE}parse_input.c\
				${PATH_PARSE}quote.c\
				${PATH_LISTS}lists_functions.c\

OBJS		= ${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

CFLAGS		= #-Wall -Wextra -Werror 

TERMLIB		=	-ltermcap -lncurses

.c.o:		
				${CC} -g ${CFLAGS}  -c -I./include/ $< -o ${<:.c=.o}

.PHONY:			all clean fclean re

$(NAME):		${OBJS} ${INCLUDE}
				@${MAKE} -C ./lib 
				@${CC} -g ${TERMLIB} ./lib/libft.a ${OBJS} -o minishell

all:			${NAME}

clean:
				${RM} ${OBJS}
				${MAKE} clean -C ./lib

fclean:			clean
				${RM} ${NAME} ./lib/libft.a

-include		${OBJ:.o=.d}

re:				fclean all
