/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:07 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 15:13:59 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setting_mlx(t_graphic *vars, t_image *img)
{
	if ((*img).ptr)
		mlx_destroy_image((*vars).mlx, (*img).ptr);
	if ((*vars).win)
		mlx_clear_window((*vars).mlx, (*vars).win);
	(*img).ptr = mlx_new_image((*vars).mlx, WIDTH, HEIGHT);
	(*img).addr = mlx_get_data_addr((*img).ptr, &(*img).bits_per_pixel, \
			&(*img).line_length, &(*img).endian);
}

void	my_mlx_pixel_put(t_image *img, t_screen *p1, int color)
{
	char	*dst;

	if (((*p1).xs < 0 || (*p1).xs >= WIDTH)
		|| (((*p1).ys < 0 || (*p1).ys >= HEIGHT)))
		return ;
	dst = img->addr + ((*p1).ys * img->line_length + \
			(*p1).xs * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
