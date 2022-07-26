/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:08:55 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/26 23:04:12 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* void point_convertor(int *x, int *y) */
/* { */
	/* *x = *x - HALF_WIDTH; */
	/* *y = *y - HALF_HEIGHT; */
/* } */
/* int angle_convert(int angle) */
/* { */
	/* return (angle * M_1_PI / 180); */
/* } */

/* void fit_info_to_screen_convert(int *x, int *y, int *theta) */
/* { */
	/* *x = *x - HALF_WIDTH; */
	/* *y = *y - HALF_WIDTH; */
	/* *theta = (double)*theta * (double)M_PI / 180; */
/* } */

/* int point_convert(int oid_x) */
/* { */
	/* return (oid_x - HALF_WIDTH); */
/* } */

/* int y_convert(int oid_y) */
/* { */
	/* return (oid_y + HALF_HEIGHT); */
/* } */
/* void inner_product_projection(t_point ***vector, t_space *map, t_data *image) */
/* { */
	/* int		i; */
	/* int		j; */

	/* i = 0; */

	/* xs =  */
	/* while (i < map->h) */
	/* { */
		/* j = 0; */

		/* while (j < map->w) */
		/* { */

			/* j++; */
		/* } */
		/* i++; */
	/* } */
/* } */
void write_origin_pixel(t_data *image, t_space *map, t_final *fnl)
{
	t_screen scn;

	scn.xs = fnl->xf + X_BASE;
	scn.ys = fnl->yf + Y_BASE;
	(void)map;
	if ((scn.xs >= 0 && scn.xs <= WIDTH)
		&& (scn.ys >= 0 && scn.ys <= HEIGHT))
		my_mlx_pixel_put(image, scn.xs, scn.ys, RGB_GREEN);
}

void put_pixel_about_map(t_point ***vector, t_space *map, t_data *image)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			write_origin_pixel(image, map, &(*vector)[i][j].final);
			/* printf("xs = %f ys = %f\n", (*vector)[i][j].screen.xs, (*vector)[i][j].screen.ys); */
			j++;
		}
		i++;
	}
}

void initializing_map(t_point ***vector, t_space *map)
{
	int		i;
	int		j;

	map->scale = 30;
	if (!vector || !map)
		return ;
	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			(*vector)[i][j].final.xf = map->scale * (j - map->w / 2);
			(*vector)[i][j].final.yf = map->scale * (i - map->h / 2);
			(*vector)[i][j].final.zf = map->scale * ((*vector)[i][j].zi);
			j++;
		}
		i++;
	}
}

/* void first_map(t_point ***vector, t_space *map) */
/* { */
	/* int		i; */
	/* int		j; */

	/* if (!vector || !map) */
		/* return ; */
	/* i = 0; */
	/* while (i < map->h) */
	/* { */
		/* j = 0; */
		/* while (j < map->w) */
		/* { */
			/* first.xf = (*vector)[i][j].xf; */
			/* first.yf = (*vector)[i][j].yf; */
			/* (*vector)[i][j].screen.xs = first.xf; */
			/* (*vector)[i][j].screen.ys = first.yf; */
			/* j++; */
		/* } */
		/* i++; */
	/* } */
/* } */

/* void zoom_in_out_map(t_point ***vector, t_space *map) */
/* { */
	/* int	i; */
	/* int	j; */

	/* map->scale += 1; */
	/* if (!vector || !map) */
		/* return ; */
	/* i = 0; */
	/* while (i < map->h) */
	/* { */
		/* j = 0; */
		/* while (j < map->w) */
		/* { */
			/* (*vector)[i][j].xf = (*vector)[i][j].xf * map->scale; */
			/* (*vector)[i][j].yf = (*vector)[i][j].yf * map->scale; */
			/* (*vector)[i][j].zf = (*vector)[i][j].zf * map->scale; */
			/* j++; */
		/* } */
		/* i++; */
	/* } */
/* } */

/* void just_rot_z(int *xi, int *yi, int x_base, int y_base, double theta) */
/* { */
	/* int x; */
	/* int y; */

	/* x = *xi - x_base; */
	/* y = *yi - y_base; */
	/* *xi = x * cos(theta) - y * sin(theta) + x_base; */
	/* *yi = x * sin(theta) + y * cos(theta) + y_base; */
/* } */


int rot_z_axis(t_final *point, double theta)
{
	double x;
	double y;

	x = point->xf;
	y = point->yf;
	point->xf = x * cos(theta * M_PI / 180) - y * sin(theta * M_PI / 180);
	point->yf = x * sin(theta * M_PI / 180) + y * cos(theta * M_PI / 180);
	return (rotation_z);
}

/* int rot_y_axis(t_final *point, double theta) */
/* { */
	/* double z; */
	/* double x; */

	/* y = point->yf; */
	/* z = point->zf; */
	/* point->xf = x * cos(theta * 180 / M_PI) - y * sin(theta * 180 / M_PI); */
	/* point->yf = x * sin(theta * 180 / M_PI) + y * cos(theta * 180 / M_PI); */
	/* return (rotation_y); */
/* } */

int rot_x_axis(t_final *point, double theta)
{
	double y;
	double z;

	y = point->yf;
	z = point->zf;
	point->yf = y * cos(theta * M_PI / 180) - z * sin(theta * M_PI / 180);
	point->zf = y * sin(theta * M_PI / 180) + z * cos(theta * M_PI / 180);
	return (rotation_x);
}

void rotate_vector(t_space *map, int (*rot)(t_final *, double)
		, double theta)
{
	t_index	idx;
	int		cur_angle;

	idx.i = 0;
	while (idx.i < map->h)
	{
		idx.j = 0;
		while (idx.j < map->w)
		{
			cur_angle = rot(&map->vector[idx.i][idx.j].final, theta);
			idx.j++;
		}
		idx.i++;
	}
	if (cur_angle == rotation_z)
		map->angle.z_axis += theta;
	else if (cur_angle == rotation_y)
		map->angle.y_axis += theta;
	else if (cur_angle == rotation_x)
		map->angle.x_axis += theta;
}

/* void rot_y(int *xi, int *yi, int x_base, int y_base, double theta) */
/* { */
	/* int x; */
	/* int y; */

	/* x = *xi - x_base; */
	/* y = *yi - y_base; */
	/* *xi = x * cos(theta) - y * sin(theta) + x_base; */
	/* *yi = x * sin(theta) + y * cos(theta) + y_base; */
/* } */

/* void rot_x(int *xi, int *yi, int x_base, int y_base, double theta) */
/* { */
	/* int x; */
	/* int y; */

	/* x = *xi - x_base; */
	/* y = *yi - y_base; */
	/* *xi = x * cos(theta) - y * sin(theta) + x_base; */
	/* *yi = x * sin(theta) + y * cos(theta) + y_base; */
/* } */

