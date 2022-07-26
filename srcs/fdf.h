/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:25:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/26 23:03:01 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <stdio.h>
# include <mlx.h>
#include "fdf_point.h"
#include "libft.h"
# include <stdlib.h>
# define WIDTH			1920.0
# define HEIGHT			1080.0
# define X_BASE			960.0
# define Y_BASE			540.0
# define ERROR			-1
# define SUCCESS		0
# define RGB_GREEN		0x0000FF00
# define iso_angle_x	35.264
# define iso_angle_z	45

enum e_angle
{
	rotation_z,
	rotation_y,
	rotation_x
};

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}	t_vars;

typedef	struct	s_index
{
	int i;
	int j;
}	t_index;

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_space
{
	int		w;
	int		h;
	double	scale;
	t_angle	angle;
	t_point	**vector;
}	t_space;


int rot_z_axis(t_final *point, double theta);
int rot_x_axis(t_final *point, double theta);
void rotate_vector(t_space *map, int (*rot)(t_final *, double)
		, double theta);
void zoom_in_out_map(t_point ***vector, t_space *map);
void first_map(t_point ***vector, t_space *map);
void put_pixel_about_map(t_point ***vector, t_space *map, t_data *image);
void	fit_info_to_screen_convert(int *x, int *y, int *theta);
int		exit_hook();
int		key_hook(int keycode, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	initializing_map(t_point ***vector, t_space *map);
void	zoom_in_out(t_point ***vector, t_space *map, int scale);
#endif

/*
<0>:No error
<1>:Operation not permitted
<2>:No such file or directory
<3>:No such process
<4>:Interrupted function call
<5>:Input/output error
<6>:No such device or address
<7>:Arg list too long
<8>:Exec format error
<9>:Bad file descriptor
<10>:No child processes
<11>:Resource temporarily unavailable
<12>:Not enough space
<13>:Permission denied
<14>:Bad address
<15>:Unknown error
<16>:Resource device
<17>:File exists
<18>:Improper link
<19>:No such device
<20>:Not a directory
<21>:Is a directory
<22>:Invalid argument
<23>:Too many open files in system
<24>:Too many open files
<25>:Inappropriate I/O control operation
<26>:Unknown error
<27>:File too large
<28>:No space left on device
<29>:Invalid seek
<30>:Read-only file system
<31>:Too many links
<32>:Broken pipe
<33>:Domain error
<34>:Result too large
<35>:Unknown error
<36>:Resource deadlock avoided
<37>:Unknown error
<38>:Filename too long
<39>:No locks available
<40>:Function not implemented
<41>:Directory not empty
<42>:Illegal byte sequence
<43>:Unknown error
<44>:Unknown error
*/
