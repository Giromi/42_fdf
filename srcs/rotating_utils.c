/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotating_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:03:51 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/29 15:54:37 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int rot_z_axis(t_vector *point, double theta)
{
	double x;
	double y;

	x = point->xf;
	y = point->yf;
	point->xf = x * cos(theta * M_PI / 180) - y * sin(theta * M_PI / 180);
	point->yf = x * sin(theta * M_PI / 180) + y * cos(theta * M_PI / 180);
	return (ROTATION_Z);
}

int rot_y_axis(t_vector *point, double theta)
{
	double z;
	double x;

	z = point->zf;
	x = point->xf;
	point->xf = x * cos(theta * M_PI / 180) + z * sin(theta * M_PI / 180);
	point->zf = -x * sin(theta * M_PI / 180) + z * cos(theta * M_PI / 180);
	return (ROTATION_Y);
}

int rot_x_axis(t_vector *point, double theta)
{
	double y;
	double z;

	y = point->yf;
	z = point->zf;
	point->yf = y * cos(theta * M_PI / 180) - z * sin(theta * M_PI / 180);
	point->zf = y * sin(theta * M_PI / 180) + z * cos(theta * M_PI / 180);
	return (ROTATION_X);
}

void rotation_value_check(t_angle *ang, int which_ang, double theta)
{
	if ((*ang).z_axis + theta >= 360 || (*ang).z_axis + theta <= -360)
		(*ang).z_axis = 0;
	if ((*ang).y_axis + theta >= 360 || (*ang).y_axis + theta <= -360)
		(*ang).y_axis = 0;
	if ((*ang).x_axis + theta >= 360 || (*ang).x_axis + theta <= -360)
		(*ang).x_axis = 0;
	if (which_ang == ROTATION_Z)
		(*ang).z_axis += theta;
	else if (which_ang == ROTATION_Y)
		(*ang).y_axis += theta;
	else if (which_ang == ROTATION_X)
		(*ang).x_axis += theta;
	printf("z : %f y : %f x : %f\n", (*ang).z_axis, (*ang).y_axis, (*ang).x_axis);
}


void rotate_vector(t_space *map, t_vector ***vec
		, int (*rot)(t_vector *, double), double theta)
{
	t_index		idx;
	int			which_angle;

	if (theta == 0)
		return ;
	idx.i = 0;
	while (idx.i < (*map).info.h)
	{
		idx.j = 0;
		while (idx.j < (*map).info.w)
		{
			which_angle = rot(&(*vec)[idx.i][idx.j], theta);
			idx.j++;
		}
		idx.i++;
	}
	rotation_value_check(&(*map).angle, which_angle, theta);
}
