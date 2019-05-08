# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 19:18:05 by hdelanoe          #+#    #+#              #
#    Updated: 2019/05/01 19:18:07 by hdelanoe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	lib34.a

# src / obj

SRC_PATH	=	.
SRC			=	$(shell find $(SRC_PATH) -name *.c)

OBJ_PATH	=	.obj
OBJ    		=	$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC))

#compiler
CC			= 	gcc
FLAGS		= 	-Wall -Wextra -Werror -g -O2

CG = \033[92m
CY = \033[93m
CE = \033[0m

all:		$(NAME)

$(NAME):	$(OBJ)
	@echo "\033[K$(CY)[LIB34] :$(CE) $(CG)Creating Library$(CE) \033[1A";
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[K$(CY)[LIB34] :$(CE) $(CG)LIB34 Compiled!$(CE)";

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)/vector
	mkdir -p $(OBJ_PATH)/matrix
	mkdir -p $(OBJ_PATH)/camera
	@ $(CC) $(FLAG) -c $< -o $@
	@ echo "\033[K$(CY)[LIB34] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:		
	
	@ /bin/rm -rf $(OBJ_PATH)

fclean:		clean
	@ /bin/rm -f $(NAME)
	@ echo "\033[K$(CY)[LIB34] :$(CE) $(CG)Library cleaned$(CE)";

re : fclean all

.PHONY: all, clean, fclean, re
.SILENT:

