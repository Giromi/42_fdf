/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:08:55 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/25 22:56:10 by minsuki2         ###   ########.fr       */
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
void inner_product_projection(t_point ***vector, t_space *map, t_data *image)
{
	int		i;
	int		j;

	i = 0;

	xs = 
	while (i < map->h)
	{
		j = 0;

		while (j < map->w)
		{

			j++;
		}
		i++;
	}
}

void write_map_pixel(t_point ***vector, t_space *map, t_data *image)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			my_mlx_pixel_put(image, (*vector)[i][j].screen.xs, (*vector[i][j]).screen.ys, RGB_GREEN);
			j++;
		}
		i++;
	}
}

void initializing_map(t_point ***vector, t_space *map)
{
	int		i;
	int		j;
	int		scale;
	t_init	origin;

	if (!vector || !map)
		return ;
	i = 0;
	scale = 20;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			origin.xi = (*vector)[i][j].init.xi;
			origin.yi = (*vector)[i][j].init.yi;
			origin.zi = (*vector)[i][j].init.zi;
			(*vector)[i][j].final.xf = origin.xi + WIDTH / 2 - map->w / 2;
			(*vector)[i][j].final.yf = origin.yi + HEIGHT / 2 - map->h / 2;
			(*vector)[i][j].final.zf = origin.zi;
			j++;
		}
		i++;
	}
}

/* void zoom_in_out_map(t_point ***vector, t_space *map, int scale) */
/* { */
	/* int	i; */
	/* int	j; */

	/* if (!vector || !map) */
		/* return ; */
	/* i = 0; */
	/* while (i++ < map->h) */
	/* { */
		/* j = 0; */
		/* while (j++ < map->w) */
		/* { */
			/* (*vector)[map->h][map->w].fixf *= scale; */
			/* (*vector)[map->h][map->w].yf *= scale; */
			/* (*vector)[map->h][map->w].zf *= scale; */
		/* } */
	/* } */
/* } */

void just_rot_z(int *xi, int *yi, int x_base, int y_base, double theta)
{
	int x;
	int y;

	x = *xi - x_base;
	y = *yi - y_base;
	*xi = x * cos(theta) - y * sin(theta) + x_base;
	*yi = x * sin(theta) + y * cos(theta) + y_base;
}


void rot_z(int *xi, int *yi, int x_base, int y_base, double theta)
{
	int x;
	int y;

	x = *xi - x_base;
	y = *yi - y_base;
	*xi = x * cos(theta) - y * sin(theta) + x_base;
	*yi = x * sin(theta) + y * cos(theta) + y_base;
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

