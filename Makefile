# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-monc <fde-monc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/14 20:22:06 by fde-monc          #+#    #+#              #
#    Updated: 2016/04/25 18:02:23 by fde-monc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

PATH_SRC = src/

SRC = 	msh_chdir.c \
		msh_env.c \
		msh_exec.c \
		msh_getcmd.c \
		msh_main.c \
		msh_splitargs.c \
		msh_tools.c

SRC_FILE = $(addprefix $(PATH_SRC), $(SRC));

OBJECTS = $(patsubst %.c,%.o,$(addprefix $(PATH_SRC), $(SRC)))

LIB = libft

LIB_EXE = libft/libft.a

all : $(NAME)

$(NAME) : $(OBJECTS) $(LIB_EXE)
	 $(CC) $(CFLAGS) -Iinc/ -L$(LIB) -lft $(OBJECTS) -o $(NAME)

$(LIB_EXE) :
	make -C $(LIB) nclean

$(OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -Iinc/ -c $< -o $@

clean :
	@rm -rf $(OBJECTS)

fclean : clean
	@rm -rf $(NAME)

re : fclean $(NAME)

nclean : all clean

nrun : all
	./minishell
