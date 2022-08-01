# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 18:42:17 by minsuki2          #+#    #+#              #
#    Updated: 2022/08/01 15:02:19 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror# -fsanitize=address
MLX_DIR 	=	minilibx_macos/
MLX_AR		=	libmlx.a
MLX 		=	mlx
APPKIT		=	AppKit
OPENGL		=	OpenGL
MLXFLAGS	=	-L$(MLX_DIR) -l$(MLX) -framework $(APPKIT) \
				-framework $(OPENGL)

COMPILE		=	-c
RM 			=	rm -vf
AR 			= ar
ARFLAGS 	= -rcus
MAKE_C 		= make -C
SRCS_DIR 	= srcs/
INCS_DIR 	= incs/
TARGET_DIR 	= $(MANDATORY_DIR)
FT			= ft

LIBFT_DIR 	=	libft/
LIBFT 		=	libft.a
NAME	 	=	fdf

MANDA_SRCS	=	fdf.c					\
				fdf_utils.c				\
				mlx_utils.c				\
				parcing.c				\
				put_pixel_utils.c		\
				rotating_utils.c		\
				hook_utils.c


# BONUS_SRCS		=a

SRCS			= 	$(addprefix $(SRCS_DIR), $(MANDA_SRCS))
HADS			=	$(MANDATORY_DIR)push_swap.h
OBJS			=	$(addprefix $(SRCS_DIR), $(MANDA_SRCS:.c=.o))

all: $(MLX_DIR)$(MLX_AR) $(LIBFT_DIR)$(LIBFT) $(NAME)

$(LIBFT_DIR)$(LIBFT):
	$(MAKE_C) $(LIBFT_DIR)

$(MLX_DIR)$(MLX_AR):.
	$(MAKE_C) $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) $(MLXFLAGS) $(SRCS) $(LIBFT_DIR)get_next_line.c -L$(LIBFT_DIR) -l$(FT) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(INCS_DIR) -o  $@
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@echo ">>>>>>>>>> fdf Compiled! <<<<<<<<<<"
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#$(CC) $(CFLAGS) $(MLXFLAGS) $(MANDA_SRCS) $(INC)$(MLX) -o $@
#$(LIBFT_DIR)$(LIBFT) $(INC)$(LIBFT_DIR)

%.o: %.c
	@echo $@ Making...:
	$(CC) $(CFLAGS) $(COMPILE) $< -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(INCS_DIR) -o $@
#$(INC)$(LIBFT_DIR)

clean:
	$(MAKE_C) $(MLX_DIR) clean
	$(MAKE_C) $(LIBFT_DIR) clean
	@echo
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(addprefix $(SRCS_DIR), $(MANDA_SRCS:.c=.o))
	@$(RM) $(addprefix $(SRCS_DIR), $(BONUS_SRCS:.c=.o))
	@echo ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<"
	@echo

fclean: clean
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_DIR)$(LIBFT)
	@echo ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<"
	@echo

re:
	@make fclean
	@make all

bonus: $(LIBFT_DIR)$(LIBFT)
	@$(MAKE) \
	"NAME 			=	$(BONUS_NAME)"									\
	"OBJS			=	$(addprefix $(BONUS_DIR), $(BONUS_SRCS:.c=.o))"	\
	"HADS			=	$(BONUS_DIR)push_swap_bonus.h"					\

.PHONY: all clean fclean re bonus
