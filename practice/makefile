# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 18:42:17 by minsuki2          #+#    #+#              #
#    Updated: 2022/07/26 17:50:01 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
MLX_DIR 		= ../minilibx_mms_20210621/
MLX_AR 			= libmlx.dylib
MLX 			= mlx
APPKIT			= AppKit
OPENGL			= OpenGL
MLXFLAGS		= -l$(MLX) -framework $(APPKIT) -framework $(OPENGL)
LIBFLAGS		= -l

COMPILE			= -c
INC 			= -I
RM 				= rm -vf
AR 				= ar
ARFLAGS 		= -rcus
MAKE_C 			= make -C
SRCS_DIR 		= ./
INCS_DIR 		= ./
TARGET_DIR 		= $(MANDATORY_DIR)
FT				= ft

LIBFT_DIR 		=	../libft/
LIBFT 			=	libft.a
NAME	 		=	fdf

MANDA_SRCS		=	euler_rotation.c
					# utils.c

SRCS 			=	$(addprefix $(SRCS_DIR), $(MANDA_SRCS))
HADS			=	$(MANDATORY_DIR)push_swap.h
OBJS			=	$(addprefix $(SRCS_DIR), $(MANDA_SRCS:.c=.o))

all: $(MLX_DIR)$(MLX_AR) $(LIBFT_DIR)$(LIBFT) $(NAME)

$(LIBFT_DIR)$(LIBFT):
	$(MAKE_C) $(LIBFT_DIR)

$(MLX_DIR)$(MLX_AR):
	$(MAKE_C) $(MLX_DIR)

$(NAME): $(OBJS)
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	$(CC) -g $(CFLAGS) $(MLXFLAGS) $(SRCS) -L$(LIBFT_DIR) $(LIBFLAGS)$(FT) $(INC)$(MLX_DIR) $(INC)$(LIBFT_DIR) -o $@
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@echo fdf_practice Compiled!

%.o: %.c
	@echo $@ Making...:
	$(CC) $(CFLAGS) $(COMPILE) $< $(INC)$(MLX_DIR) $(INC)$(LIBFT_DIR) -o $@
#$(INC)$(LIBFT_DIR)

clean:
	$(MAKE_C) $(MLX_DIR) clean
	@echo
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(addprefix $(MANDATORY_DIR), $(SRCS:.c=.o))
	@echo ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<"
	@echo

fclean: clean
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(NAME)
	@echo ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<"
	@echo

re:
	@make fclean
	@make all

.PHONY: all clean fclean re bonus
