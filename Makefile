# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:42:08 by ctacconi          #+#    #+#              #
#    Updated: 2024/06/12 19:54:26 by carolinatac      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = srcs/pipex.c srcs/utils.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDE = Makefile pipex.h

RM = rm -f

# Implicit method
%.o: %.c Makefile inc/pipex.h ft_printf/libftprintf.a
	$(CC) $(CFLAGS) -Imlx -o $@ -c $<

# My methods
all: make_libs $(NAME)

make_libs:
	Make -C ft_printf/

$(NAME): $(OBJ) 
	cp ft_printf/libftprintf.a $(NAME)
	$(CC) $(NAME) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	Make -C ft_printf/ clean

fclean: clean
	$(RM) $(NAME)
	Make -C ft_printf/ fclean

re: fclean all

.PHONY: all clean fclean re
