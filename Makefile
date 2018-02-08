# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcheung <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/06 20:20:10 by kcheung           #+#    #+#              #
#    Updated: 2017/05/19 19:00:00 by kcheung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fdf
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAG = -framework OpenGL -framework AppKit

SRC_DIR = ./srcs/
SRC_NAME = main.c \
		   bresenham.c \
		   drawing.c \
		   handle_events.c \
		   init.c \
		   memory.c \
		   rotate.c
SRCS = $(addprefix $(SRC_DIR),$(SRC_NAME))

OBJ_DIR = ./obj/
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJS = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_PATH = ./libft/
LIBFT = $(LIB_PATH)/libft.a
LIB_LINK = -L $(LIB_PATH) -lft 

INC_DIR = ./includes/
INC = -I $(LIB_PATH)$(INC_DIR) -I$(INC_DIR)

MLX_PATH = ./ft_libgfx/minilibx_macos_elcapitan
MLXLIB = $(MLX_PATH)/libmlx.a
MLX_LINK = -L $(MLX_PATH) -lft 


# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)


all: obj  $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB_LINK) $(MLXFLAG) $(MLX_LINK)
	@chmod 755 $@
	@echo "Compiling" [$(NAME)] $(SUCCESS)

# @ evals to NAME
# ^ evals to OBS LIB

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)*.h
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "Linking" [$<] $(OK)

$(LIBFT):
	@make -C $(LIB_PATH)

$(MLXLIB):
	@make -C $(MLX_PATH)

obj:
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(WAC)FdF:\t\tRemoving OBJ path: ./obj/"
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_PATH) clean
	@make -C $(MLX_PATH) clean
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)
	
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all
