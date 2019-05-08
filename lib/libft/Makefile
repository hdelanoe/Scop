#***************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/10 15:45:37 by hdelanoe          #+#    #+#              #
#    Updated: 2017/06/14 18:30:11 by hdelanoe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC			=	ft_atod.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_isdigit.c \
				ft_kill.c \
				ft_memalloc.c \
				ft_memset.c \
				ft_putchar.c \
				ft_putendl.c \
				ft_putnbr.c \
				ft_putstr.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnew.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_tabfree.c \
				get_next_line.c \

OBJ    		=	$(patsubst %.c,.obj/%.o,$(SRC))

CC	= gcc
FLAGS = -Wall -Werror -Wextra -g -O2
CG = \033[92m
CY = \033[93m
CE = \033[0m

all: 			$(NAME)
$(NAME)	: $(OBJ)
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CG)Creating Library$(CE) \033[1A";
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CG)LIBFT Compiled!$(CE)";

.obj/%.o: %.c
	mkdir -p .obj
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean: 
	@ /bin/rm -rf .obj

fclean: 		clean
	@ /bin/rm -f $(NAME)
	@echo "\033[K$(CY)[LIBFT] :$(CE) $(CG)Cleaning Library$(CE)";

re: 			fclean all

.PHONY: all, clean, fclean, re
.SILENT:
