# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 18:20:11 by carolinatac       #+#    #+#              #
#    Updated: 2024/05/30 18:31:56 by carolinatac      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = srcs/main.c

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
	#Make -C mlx/
	Make -C ft_printf/

$(NAME): $(OBJ) 
	cp ft_printf/libftprintf.a $(NAME)
	$(CC) $(NAME) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	$(RM) $(OBJ)
	#Make -C mlx/ clean
	Make -C ft_printf/ clean

fclean: clean
	$(RM) $(NAME)
	Make -C ft_printf/ fclean

re: fclean all

.PHONY: all clean fclean re
