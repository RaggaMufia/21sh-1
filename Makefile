#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skavunen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/14 13:21:34 by skavunen          #+#    #+#              #
#    Updated: 2017/08/22 18:29:01 by skavunen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 21sh

SRC =	main.c \
		ft_21.c \
		init.c \
		tools.c \
		input.c \
		quote.c \
		args.c \
		arrows.c \
		tab.c \
		backspace.c \
		hist.c \
		ft_cmd.c \
		find.c \
		redirect.c \
		leaks.c \
		check.c \
		search.c \
		command.c \
		execute.c \
		pipes.c \
		exepipes.c \
		cd.c \
		env.c \
		heredoc.c \
		advanced.c \
		ctrlarr.c \

OBJ = $(SRC:.c=.o)

HEADER = ft_shell.h libft/libft.h

CC = gcc

LIBFTDIR = libft/

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFTDIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFTDIR) -lft -lncurses

$(LIBFTDIR)libft.a: libft/Makefile
	make -C libft/

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFTDIR)libft.a

re: clean all
