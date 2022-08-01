# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 18:42:17 by minsuki2          #+#    #+#              #
#    Updated: 2022/08/01 15:48:38 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror
MLX_DIR 	=	minilibx_macos/
MLX_AR		=	libmlx.a
MLX 		=	mlx
APPKIT		=	AppKit
OPENGL		=	OpenGL
MLXFLAGS	=	-L$(MLX_DIR) -l$(MLX) -framework $(APPKIT) \
				-framework $(OPENGL)

COMPILE		=	-c
RM 			=	rm -vf
AR 			=	ar
ARFLAGS 	=	-rcus
MAKE_C 		=	make -C
SRCS_DIR 	=	srcs/
INCS_DIR 	=	incs/
FT			=	ft

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

BONUS_SRCS		=	fdf_bonus.c					\
					fdf_utils_bonus.c			\
					mlx_utils_bonus.c			\
					parcing_bonus.c				\
					put_pixel_utils_bonus.c		\
					rotating_utils_bonus.c		\
					hook_utils_bonus.c

OBJS			=	$(addprefix $(SRCS_DIR), $(MANDA_SRCS))

all: $(MLX_DIR)$(MLX_AR) $(LIBFT_DIR)$(LIBFT) $(NAME)

$(LIBFT_DIR)$(LIBFT):
	$(MAKE_C) $(LIBFT_DIR)

$(MLX_DIR)$(MLX_AR):
	$(MAKE_C) $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -L$(LIBFT_DIR) -l$(FT) -I$(MLX_DIR) \
		-I$(LIBFT_DIR) -I$(INCS_DIR) -o  $@
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@echo ">>>>>>>>>> fdf Compiled! <<<<<<<<<<"
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%.o: %.c
	@echo $@ Making...:
	$(CC) $(CFLAGS) $(COMPILE) $< -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(INCS_DIR) -o $@

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
	@$(MAKE) 														\
	"OBJS		= 	$(addprefix $(SRCS_DIR), $(BONUS_SRCS:.c=.o))"	\
	all

.PHONY: all clean fclean re bonus
