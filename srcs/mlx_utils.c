/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:07 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/28 20:47:59 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
# include <stdio.h>
// esc key press event
//
//
//
/* int		fdf_loop(t_main *fdf) */
/* { */
	/* mlx_destroy_image((*fdf).vars.mlx, (*fdf).vars.win); */

	/* return (SUCCESS); */
/* } */
//
void event_rotate(int keycode, t_space *map, t_vector ***vec)
{
	/* if (keycode == VAL_KEY_W) */
	if (keycode == VAL_KEY_W)
		rotate_vector(map, vec, rot_x_axis, 15);
	else if (keycode == VAL_KEY_S)
		rotate_vector(map, vec, rot_x_axis, -15);
	else if (keycode == VAL_KEY_A)
		rotate_vector(map, vec, rot_z_axis, -15);
	else if (keycode == VAL_KEY_D)
		rotate_vector(map, vec, rot_z_axis, +15);
	else if (keycode == VAL_KEY_Q)
		rotate_vector(map, vec, rot_y_axis, -15);
	else if (keycode == VAL_KEY_E)
		rotate_vector(map, vec, rot_y_axis, +15);
		/* (*deg).z_axis = +30; */
	/* if (keycode == VAL_KEY_S) */
}

void redraw(t_graphic *vars, t_image *img, t_space *map, t_vector ***vec)
{
	ft_bzero(&(*map).deg, sizeof(t_angle));
	put_pixel_about_map(img, map, vec);
	printf("Here!\n");
	mlx_put_image_to_window((*vars).mlx, (*vars).win, (*img).ptr, 0, 0);
}

void setting_mlx(t_main	*fdf)
{
	mlx_destroy_image((*fdf).vars.mlx, (*fdf).img.ptr);
	mlx_clear_window((*fdf).vars.mlx, (*fdf).vars.win);
	(*fdf).img.ptr = mlx_new_image((*fdf).vars.mlx, WIDTH, HEIGHT);
	 // 이미지 객체 생성
	(*fdf).img.addr = mlx_get_data_addr((*fdf).img.ptr, &(*fdf).img.bits_per_pixel, &(*fdf).img.line_length, &(*fdf).img.endian);
}

int	key_hook(int keycode, t_main *fdf)
{
	setting_mlx(fdf);
	if (keycode == VAL_KEY_ESC)
		exit_hook(fdf);
	event_rotate(keycode, &(*fdf).map, &(*fdf).vec);
	redraw(&(*fdf).vars, &(*fdf).img, &(*fdf).map, &(*fdf).vec);
	return (SUCCESS);
}


/* int	(t_main *fdf) */
/* { */
	/* return (SUCCESS); */
/* } */



int exit_hook(t_main *fdf)
{
	all_clean((void **)(*fdf).vec);
	mlx_clear_window((*fdf).vars.mlx, (*fdf).vars.win);
	mlx_destroy_image((*fdf).vars.mlx, (*fdf).img.ptr);
	mlx_destroy_window((*fdf).vars.mlx, (*fdf).vars.win);
	exit(0);
}
	/* mlx_clear_window((*fdf).vars.mlx, (*fdf).vars.win); */

//원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void	my_mlx_pixel_put(t_space *map, t_image *img, t_screen *p1, int color)
{
	int x;
	int y;
	char	*dst;

	x = (*p1).xs + (*map).base.xs;
	y = (*p1).ys + (*map).base.ys;
	/* if ((x < 0 || x >= WIDTH) || (y < 0 || y > HEIGHT)) */
		/* return ; */
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
