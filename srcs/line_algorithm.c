/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 00:25:07 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/29 16:43:41 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void  gradient_below_one(t_image *img, t_space *map, t_line *set, t_screen *add)
{
	double	recurr_eqn;

	recurr_eqn = 2 * (*set).delta.ys - (*set).delta.xs;
	while ((int)(*set).p1.xs != (int)(*set).p2.xs)
	{
		if (recurr_eqn < 0)
			recurr_eqn += 2 * (*set).delta.ys;
		else
		{
			(*set).p1.ys += add->ys;
			recurr_eqn += 2 * ((*set).delta.ys) - 2 * ((*set).delta.xs);
		}
		my_mlx_pixel_put(map, img, &(*set).p1, RGB_GREEN);
		(*set).p1.xs += add->xs;
	}
}

void  gradient_above_one(t_image *img, t_space *map, t_line *set, t_screen *add)
{
	double	recurr_eqn;

	recurr_eqn = 2 * (*set).delta.xs - (*set).delta.ys;
	while ((int)(*set).p1.ys != (int)(*set).p2.ys)
	{
		if (recurr_eqn < 0)
			recurr_eqn += 2 * (*set).delta.xs;
		else
		{
			(*set).p1.xs += add->xs;
			recurr_eqn += 2 * ((*set).delta.xs) - 2 * ((*set).delta.ys);
		}
		my_mlx_pixel_put(map, img, &(*set).p1, RGB_GREEN);
		(*set).p1.ys += add->ys;
	}
}

/* void bresenham_line(t_data *image, t_line *set */
		/* , void (*gradient_one)(t_data *, t_line *, t_screen *)) */
/* { */
	/* [> else// if (set.delta.xs <= set.delta.ys) <] */
		/* [> bresenham_line(image, &set, gradient_above_one); <] */
/* } */
