# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 18:01:15 by dpavon-g          #+#    #+#              #
#    Updated: 2021/09/01 10:11:00 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = server
NAME2 = client

SRCS1 = 	ft_server/server.c
SRCS2 =		ft_client/client.c

LIB_PATH = libft/
LIB_NAME = $(LIB_PATH)libft.a
INCLUDES = -I. -I includes/minitalk.h
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME) $(NAME2)

$(NAME): $(SRCS1)
	make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(SRCS1) $(INCLUDES) -L ./libft/ -lft -o $(NAME)

$(NAME2): $(SRCS2)
	make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(SRCS2) $(INCLUDES) -L ./libft/ -lft -o $(NAME2)

clean:
	@make -C $(LIB_PATH) clean
	@rm -f $(OBJECTS)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -f $(NAME)
	@rm -f $(NAME2)

re: fclean all

.PHONY:	all clean fclean re
