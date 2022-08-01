/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:25:02 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 15:15:22 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	gradient_below_one(t_image *img, t_line *set, t_screen *add)
{
	int	recurr_eqn;

	recurr_eqn = 2 * (*set).delta.ys - (*set).delta.xs;
	while ((*set).p1.xs != (*set).p2.xs)
	{
		if (recurr_eqn < 0)
			recurr_eqn += 2 * (*set).delta.ys;
		else
		{
			(*set).p1.ys += add->ys;
			recurr_eqn += 2 * ((*set).delta.ys) - 2 * ((*set).delta.xs);
		}
		my_mlx_pixel_put(img, &(*set).p1, RGB_GREEN);
		(*set).p1.xs += add->xs;
	}
}

static void	gradient_above_one(t_image *img, t_line *set, t_screen *add)
{
	int	recurr_eqn;

	recurr_eqn = 2 * (*set).delta.xs - (*set).delta.ys;
	while ((*set).p1.ys != (*set).p2.ys)
	{
		if (recurr_eqn < 0)
			recurr_eqn += 2 * (*set).delta.xs;
		else
		{
			(*set).p1.xs += add->xs;
			recurr_eqn += 2 * ((*set).delta.xs) - 2 * ((*set).delta.ys);
		}
		my_mlx_pixel_put(img, &(*set).p1, RGB_GREEN);
		(*set).p1.ys += add->ys;
	}
}

static void	find_max_min_screen(t_space *map, t_screen *p1)
{
	if ((*map).max.xs < (*p1).xs)
		(*map).max.xs = (*p1).xs;
	if ((*map).max.ys < (*p1).ys)
		(*map).max.ys = (*p1).ys;
	if ((*map).min.xs > (*p1).xs)
		(*map).min.xs = (*p1).xs;
	if ((*map).min.ys > (*p1).ys)
		(*map).min.ys = (*p1).ys;
}

static void	write_origin_pixel(t_image *img, t_space *map, t_vector *f1
		, t_vector *f2)
{
	t_line		set;
	t_screen	add;

	set.p1.xs = round((*map).scale * f1->xf) + (*map).base.xs;
	set.p1.ys = round((*map).scale * f1->yf) + (*map).base.ys;
	set.p2.xs = round((*map).scale * f2->xf) + (*map).base.xs;
	set.p2.ys = round((*map).scale * f2->yf) + (*map).base.ys;
	set.delta.xs = set.p2.xs - set.p1.xs;
	set.delta.ys = set.p2.ys - set.p1.ys;
	if (set.delta.xs < 0)
		set.delta.xs *= -1;
	if (set.delta.ys < 0)
		set.delta.ys *= -1;
	add.xs = 1 - 2 * (set.p1.xs > set.p2.xs);
	add.ys = 1 - 2 * (set.p1.ys > set.p2.ys);
	if (set.delta.ys < set.delta.xs)
		gradient_below_one(img, &set, &add);
	else
		gradient_above_one(img, &set, &add);
	find_max_min_screen(map, &set.p1);
}

void	put_pixel_about_map(t_image *img, t_space *map, t_vector ***vec)
{
	t_index	idx;

	idx.i = 0;
	(*map).max.xs = round((*map).scale * (*vec)[0][0].xf) + (*map).base.xs;
	(*map).max.ys = round((*map).scale * (*vec)[0][0].yf) + (*map).base.ys;
	(*map).min.xs = round((*map).scale * (*vec)[0][0].xf) + (*map).base.xs;
	(*map).min.ys = round((*map).scale * (*vec)[0][0].yf) + (*map).base.ys;
	while (idx.i < (*map).info.h)
	{
		idx.j = 0;
		while (idx.j < (*map).info.w)
		{
			if (idx.j < (*map).info.w - 1)
				write_origin_pixel(img, map, &(*vec)[idx.i][idx.j], \
						&(*vec)[idx.i][idx.j + 1]);
			if (idx.i < (*map).info.h - 1)
				write_origin_pixel(img, map, &(*vec)[idx.i][idx.j], \
						&(*vec)[idx.i + 1][idx.j]);
			idx.j++;
		}
		idx.i++;
	}
}
