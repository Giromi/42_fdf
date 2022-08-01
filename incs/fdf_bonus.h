/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:25:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 15:27:11 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# include <math.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# include "fdf_point.h"
# include <stdlib.h>
# define WIDTH						1920.0
# define HEIGHT						1080.0
# define X_ORIGIN					960.0
# define Y_ORIGIN					540.0
# define ERROR						-1
# define SUCCESS					0
# define ISO_ANGLE_X_AXIS			54.736
# define ISO_ANGLE_Z_AXIS			45.0
# define VAL_KEY_HOOK				2
# define VAL_MOUSE_HOOK				4
# define VAL_EXIT_HOOK				17
# define RGB_GREEN					0x0000FF00
# define RGB_WHITE					0x00FFFFFF
# define VAL_INT_MIN				2147483648
# define VAL_INT_MAX				2147483647

enum e_angle
{
	ROTATION_Z,
	ROTATION_Y,
	ROTATION_X,
};

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_initial
{
	int			w;
	int			h;
}	t_initial;

typedef struct s_space
{
	t_initial	info;
	double		init_scale;
	double		scale;
	t_angle		angle;
	t_screen	base;
	t_screen	max;
	t_screen	min;
}	t_space;

typedef struct s_graphic
{
	void		*mlx;
	void		*win;
}	t_graphic;

typedef struct s_main
{
	t_graphic	vars;
	t_image		img;
	t_space		map;
	t_vector	**vec;
}	t_main;

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

void		redraw(t_graphic *var, t_image *img, t_space *map, t_vector ***vec);
void		initializing_map(t_space *map, t_vector ***vec);
void		put_pixel_about_map(t_image *img, t_space *map, t_vector ***vec);
void		my_mlx_pixel_put(t_image *img, t_screen *p1, int color);
int			is_set(char *set, char c);
int			exit_hook(t_main *fdf);
void		fdf_hook_loop(t_main *fdf);
int			key_hook(int keycode, t_main *fdf);
int			mouse_hook(int button, int x, int y, t_main *fdf);
void		setting_mlx(t_graphic *vars, t_image *img);
t_vector	**check_map(char *file, t_space *map);
int			rot_z_axis(t_vector *point, double theta);
int			rot_y_axis(t_vector *point, double theta);
int			rot_x_axis(t_vector *point, double theta);
void		rotate_vector(t_space *map, t_vector ***vector, \
		int (*rot)(t_vector *, double), double theta);
int			line_to_split(int fd, char ***split_line);
void		ft_clean_error(t_vector **vec, char **split_line, char *str);
void		ft_error(char *str);
void		all_clean(void **object);
#endif
