/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:16:47 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/31 23:40:33 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void event_rotate(int keycode, t_space *map, t_vector ***vec) {
	/* if (keycode == VAL_KEY_W) */
	if (keycode == VAL_KEY_W)
		rotate_vector(map, vec, rot_x_axis, 10);
	else if (keycode == VAL_KEY_S)
		rotate_vector(map, vec, rot_x_axis, -10);
	else if (keycode == VAL_KEY_A)
		rotate_vector(map, vec, rot_z_axis, -10);
	else if (keycode == VAL_KEY_D)
		rotate_vector(map, vec, rot_z_axis, +10);
	else if (keycode == VAL_KEY_Q)
		rotate_vector(map, vec, rot_y_axis, -10);
	else if (keycode == VAL_KEY_E)
		rotate_vector(map, vec, rot_y_axis, +10);
}

static void event_move(int keycode, t_space *map)
{
	int shift;

	shift = 20;
	if (keycode == VAL_KEY_UP && (*map).max.ys > 0)
		(*map).base.ys -= shift;
	else if (keycode == VAL_KEY_DOWN && (*map).min.ys < HEIGHT)
		(*map).base.ys += shift;
	else if (keycode == VAL_KEY_LEFT && (*map).max.xs > 0)
		(*map).base.xs -= shift;
	else if (keycode == VAL_KEY_RIGHT && (*map).min.xs < WIDTH)
		(*map).base.xs += shift;
}

static void	event_project(int keycode, t_space *map, t_vector ***vec)
{
	if (!(keycode ==  VAL_KEY_R || keycode == VAL_KEY_ONE
			|| keycode == VAL_KEY_TWO || keycode == VAL_KEY_THREE))
		return ;
	initializing_map(map, vec);
	if (keycode == VAL_KEY_R)
	{
		rotate_vector(map, vec, rot_z_axis, ISO_ANGLE_Z_AXIS);
		rotate_vector(map, vec, rot_x_axis, ISO_ANGLE_X_AXIS);
	}
	else if (keycode == VAL_KEY_TWO)
	{
		rotate_vector(map, vec, rot_y_axis, 90);
		rotate_vector(map, vec, rot_z_axis, -90);
	}
	else if (keycode == VAL_KEY_THREE)
		rotate_vector(map, vec, rot_x_axis, 90);
}

void redraw(t_graphic *vars, t_image *img, t_space *map, t_vector ***vec)
{
	put_pixel_about_map(img, map, vec);
	printf("min : %d %d\n", (*map).min.xs, (*map).min.ys);
	printf("max : %d %d\n\n", (*map).max.xs, (*map).max.ys);
	mlx_put_image_to_window((*vars).mlx, (*vars).win, (*img).ptr, 0, 0);
	/* find_max_min_screen(map, vec); */
}

int	key_hook(int keycode, t_main *fdf)
{
	setting_mlx_map(&(*fdf).vars, &(*fdf).img, &(*fdf).map);
	if (keycode == VAL_KEY_ESC)
		exit_hook(fdf);
	event_rotate(keycode, &(*fdf).map, &(*fdf).vec);
	event_move(keycode, &(*fdf).map);
	event_project(keycode, &(*fdf).map, &(*fdf).vec);
	redraw(&(*fdf).vars, &(*fdf).img, &(*fdf).map, &(*fdf).vec);
	return (SUCCESS);
}
