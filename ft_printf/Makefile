# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 16:04:04 by ctacconi          #+#    #+#              #
#    Updated: 2024/06/26 12:52:41 by ctacconi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRC=ft_printf.c \
	ft_put_unbr.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putnbr.c \
	ft_puthex.c \
	ft_putptr.c

OBJ=$(SRC:.c=.o)

CC=cc

CFLAGS= -Wall -Wextra -Werror

INCLUDE= Makefile ft_printf.h

LIB=ar rcs

RM=rm -f

# Metodo implicito
%.o: %.c Makefile ft_printf.h libft/libft.a
	$(CC) $(CFLAGS) -o $@ -c $<


# Mis metodos 
all: make_libs $(NAME)

make_libs:
	make -C libft/

$(NAME): $(OBJ)
	cp libft/libft.a $(NAME)
	$(LIB) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)
	make -C libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
