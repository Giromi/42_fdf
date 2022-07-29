/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_point.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:17:12 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/29 16:53:05 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_POINT_H
# define FDF_POINT_H
# define VAL_KEY_ESC			53
# define VAL_KEY_UP				126
# define VAL_KEY_DOWN			125
# define VAL_KEY_LEFT			123
# define VAL_KEY_RIGHT			124
# define VAL_KEY_W				13
# define VAL_KEY_A				0
# define VAL_KEY_S				1
# define VAL_KEY_D				2
# define VAL_KEY_Q				12
# define VAL_KEY_E				14
# define VAL_KEY_ONE			18
# define VAL_KEY_TWO			19
# define VAL_KEY_THREE			20
# define VAL_MOU_HEEL_UP		4
# define VAL_MOU_HEEL_DOWN		5

typedef struct s_screen
{
	int xs;
	int ys;
}	t_screen;

typedef struct s_angle
{
	double	z_axis;
	double	y_axis;
	double	x_axis;
}	t_angle;

typedef struct s_vector
{
	double		xf;
	double		yf;
	double		zf;
	int			zi;
	t_screen	scn;
}	t_vector;

typedef struct s_line
{
	t_screen	p1;
	t_screen	p2;
	t_screen	delta;
}	t_line;

#endif
