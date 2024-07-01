# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:42:08 by ctacconi          #+#    #+#              #
#    Updated: 2024/07/01 22:31:46 by ctacconi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = srcs/pipex.c srcs/utils.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

INCLUDE = Makefile inc/pipex.h ft_printf/libftprintf.a

RM = rm -f

# Regla implícita para compilar archivos .o desde .c
%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

# Reglas para el makefile
all: make_libs $(NAME)

make_libs:
	make -C ft_printf/

$(NAME): $(OBJ)
	$(CC) $(OBJ) ft_printf/libftprintf.a -o $(NAME)

clean:
	make -C ft_printf/ clean
	$(RM) $(OBJ)

fclean: clean
	make -C ft_printf/ fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
