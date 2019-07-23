# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/04 17:30:00 by rvan-der          #+#    #+#              #
#    Updated: 2019/07/23 18:33:33 by rvan-der         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SHELL = /bin/sh
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
LDFLAGS = -dynamiclib -L./libft -lft

INCLUDE = ./include

SRC = ./src/malloc.c ./src/free.c ./src/mapping_fts.c \
		./src/pool_tab_api.c ./src/pool_tab_operations.c \
		./src/alloc_ts.c ./src/data_lock.c ./src/realloc.c\
		./src/pool_fts.c ./src/calloc.c


OBJ = ./obj/malloc.o ./obj/free.o ./obj/mapping_fts.o \
		./obj/pool_tab_api.o ./obj/pool_tab_operations.o \
		./obj/alloc_ts.o ./obj/data_lock.o ./obj/realloc.o\
		./obj/pool_fts.o ./obj/calloc.o

LINK_NAME = libft_malloc.so

LIB_NAME = libft_malloc_$(HOSTTYPE).so

.SUFFIXES:

all: $(LINK_NAME)

$(LINK_NAME): $(LIB_NAME)
	ln -s ./$(LIB_NAME) ./$(LINK_NAME)

$(LIB_NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $(LIB_NAME) $(OBJ)

$(OBJ): $(SRC) libft/libft.a
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)
	@mv ./*.o ./obj/
	@rm -f $(LINK_NAME)

libft/libft.a:
	make -C ./libft

clean:
	@make -C ./libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C ./libft fclean
	@rm -f ./$(LINK_NAME)
	@rm -f ./$(LIB_NAME)

re: fclean all