/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:08:55 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/29 16:55:17 by minsuki2         ###   ########.fr       */
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
/* void inner_product_projection(t_vector ***vector, t_space *map, t_data *image) */
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

void write_origin_pixel(t_image *img, t_space *map, t_vector *p1, t_vector *p2)
{
	t_line		set;
	t_screen	add;

	set.p1.xs = round((*map).info.scale * p1->xf);
	set.p1.ys = round((*map).info.scale * p1->yf);
	set.p2.xs = round((*map).info.scale * p2->xf);
	set.p2.ys = round((*map).info.scale * p2->yf);
	set.delta.xs = set.p2.xs - set.p1.xs;
	set.delta.ys = set.p2.ys - set.p1.ys;
	/* printf("p1 : %f %f => %d %d\n", p1->xf, p1->yf, set.p1.xs, set.p1.ys); */
	/* printf("p2 : %f %f => %d %d\n", p2->xf, p2->yf, set.p2.xs, set.p2.ys); */
	/* printf("d  : %d %d\n", set.delta.xs, set.delta.ys); */
	if (set.delta.xs < 0)
		set.delta.xs *= -1;
	if (set.delta.ys < 0)
		set.delta.ys *= -1;
	add.xs = 1 - 2 * (set.p1.xs > set.p2.xs);
	add.ys = 1 - 2 * (set.p1.ys > set.p2.ys);
	if (set.delta.ys < set.delta.xs)
		gradient_below_one(img, map, &set, &add);
	else
		gradient_above_one(img, map, &set, &add);
	(*map).scn.xs = set.p1.xs;
	(*map).scn.ys = set.p1.ys;

}
	/* my_mlx_pixel_put(img, set.p1.xs, set.p1.ys, RGB_GREEN); */

void	put_pixel_about_map(t_image *img, t_space *map, t_vector ***vec)
{
	t_index	idx;

	idx.i = 0;
	while (idx.i < (*map).info.h)
	{
		idx.j = 0;
		while (idx.j < (*map).info.w)
		{
			if (idx.j < (*map).info.w - 1)
				write_origin_pixel(img, map, &(*vec)[idx.i][idx.j], &(*vec)[idx.i][idx.j + 1]);
			if (idx.i < (*map).info.h - 1)
				write_origin_pixel(img, map, &(*vec)[idx.i][idx.j], &(*vec)[idx.i + 1][idx.j]);
			idx.j++;
		}
		idx.i++;
	}
}
			/* printf("xs = %f ys = %f\n", (*vector)[i][j].screen.xs, (*vector)[i][j].screen.ys); */
/* void find_scale */
/* { */

/* } */

void initializing_map(t_space *map, t_vector ***vec)
{
	t_index	idx;

	(*map).info.scale = 30;
	(*map).base.xs = X_ORIGIN;
	(*map).base.ys = Y_ORIGIN;
	/* (*map).deg.z_axis = ISO_ANGLE_Z_AXIS; */
	/* (*map).deg.x_axis = ISO_ANGLE_X_AXIS; */
	if (!vec || !map)
		return ;
	idx.i = 0;
	while (idx.i < (*map).info.h)
	{
		idx.j = 0;
		while (idx.j < (*map).info.w)
		{
			(*vec)[idx.i][idx.j].xf = idx.j - (*map).info.w / 2;
			(*vec)[idx.i][idx.j].yf = idx.i - (*map).info.h / 2;
			(*vec)[idx.i][idx.j].zf = (*vec)[idx.i][idx.j].zi;
			idx.j++;
		}
		idx.i++;
	}
}

/* void first_map(t_vector ***vector, t_space *map) */
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

/* void zoom_in_out_map(t_vector ***vector, t_space *map) */
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

void	vec_is_possible_move(t_space *map, t_vector ***vec, int shift)
{
	t_index	idx;
	char		bit_move;

	idx.i = 0;
	while (idx.i < (*map).info.h)
	{
		idx.j = 0;
		while (idx.j < (*map).info.w)
		{
			if ((*map).info.scale * (*vec)[idx.i][idx.j].xf + + (*map))shift
			if ((*vec)[idx.i][idx.j].xf + shift)

				write_origin_pixel(img, map, , &);
			if (idx.i < (*map).info.h - 1)
				write_origin_pixel(img, map, &(*vec)[idx.i][idx.j], &(*vec)[idx.i + 1][idx.j]);
			idx.j++;
		}
		idx.i++;
	}
	return (bit_move);
}

void all_clean(void **object)
{
	int i;

	if (!object)
		return ;
	i = 0;
	while (object[i])
		free(object[i++]);
	if (object)
	free(object);
}

char *ft_problem(t_vector **vec, char **split_line)
{
	if (vec)
		all_clean((void **)vec);
	if (split_line)
		all_clean((void **)split_line);
	exit(1);
}
