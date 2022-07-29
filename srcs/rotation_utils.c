/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:03:51 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/28 20:50:47 by minsuki2         ###   ########.fr       */
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
	if (which_angle == ROTATION_Z)
		map->angle.z_axis += theta;
	else if (which_angle == ROTATION_Y)
		map->angle.y_axis += theta;
	else if (which_angle == ROTATION_X)
		map->angle.x_axis += theta;
}
