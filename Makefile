# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/12 11:53:09 by hdelanoe          #+#    #+#              #
#    Updated: 2019/03/12 12:50:49 by hdelanoe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	scop

# src / obj

SRC_PATH	=	src
SRC			=	$(shell find $(SRC_PATH) -name *.c)


OBJ_PATH	=	.obj
OBJ    		=	$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC)) 

# librairies / includes

LIB_PATH	=	lib
GLFW 		= 	$(LIB_PATH)/glfw
GLAD		=	$(LIB_PATH)/glad
LIBFT 		= 	$(LIB_PATH)/libft
LIB34 		= 	$(LIB_PATH)/lib34

INC_PATH	=	include
LIB			=	$(GLFW) $(LIBFT) $(LIB34) $(GLAD)
INC 		=	$(addprefix -I,$(INC_PATH))
LINK 		=	$(addprefix -L,$(LIB))

#compiler
CC			= 	gcc
FLAGS		= 	-Wall -Wextra -Werror -g -O2
LIBFLAG		= 	-lft -l34 -lglad -lglfw -framework OpenGL -framework AppKit -framework IOKit -framework Cocoa -framework CoreVideo


CG = \033[92m
CY = \033[93m
CE = \033[0m

all:		$(NAME)

$(NAME):	$(OBJ)
	@ make -C $(LIBFT) all
	@ make -C $(LIB34) all
	@ $(CC) $(FLAGS) $(LINK) $(INC) $(LIBFLAG) -o $@ $^
	@ echo "\n$(CG)---> SCOP program created ✓$(CE)";

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/shader
	mkdir -p $(OBJ_PATH)/parsing
	@ $(CC) $(FLAG) $(INC) -c $< -o $@
	@ echo "\033[K$(CY)[SCOP] :$(CE) $(CG)Compiling $<$(CE) \033[1A";


clean:		
	
	@ /bin/rm -rf $(OBJ_PATH)
	@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m";

fclean:		clean
	@ /bin/rm -f $(NAME)
	@ echo "\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m";

re: 		fclean all

cleanlibs:
	@ make -C $(LIBFT) fclean
	@ make -C $(LIB34) fclean
	@ echo "\033[1;33m---> Libs cleared\033[2;00m \033[92m✓\033[0m";

relibs: cleanlibs 
	@ make re


.PHONY: all, clean, fclean, re
.SILENT:

