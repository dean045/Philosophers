# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 17:25:18 by brhajji-          #+#    #+#              #
#    Updated: 2022/03/11 17:53:45 by brhajji-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs

SRCS	= main.c ft_atoi.c

OBJS			=	$(addprefix $(SRC_DIR)/, $(SRCS:%.c=%.o))

NAME			=	philo

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g

RM				=	rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all:		${NAME}

bonus :		$(BONUS)	
				rm -f $(NAME)

clean:
	${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re
