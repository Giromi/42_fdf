/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:16:47 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 14:23:15 by minsuki2         ###   ########.fr       */
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

int	mouse_hook(int button, int x, int y, t_main *fdf)
{
	(void)x;
	(void)y;
	setting_mlx(&(*fdf).vars, &(*fdf).img);
	if (button == VAL_MOU_HEEL_UP && (*fdf).map.scale < 10000)
		(*fdf).map.scale += (*fdf).map.scale * 0.1;
	else if (button == VAL_MOU_HEEL_DOWN && (*fdf).map.scale > 0.0001)
		(*fdf).map.scale -= (*fdf).map.scale * 0.1;
	put_pixel_about_map(&(*fdf).img, &(*fdf).map, &(*fdf).vec);
	mlx_put_image_to_window((*fdf).vars.mlx, (*fdf).vars.win, (*fdf).img.ptr, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_main *fdf)
{
	setting_mlx(&(*fdf).vars, &(*fdf).img);
	if (keycode == VAL_KEY_ESC)
		exit_hook(fdf);
	event_rotate(keycode, &(*fdf).map, &(*fdf).vec);
	event_move(keycode, &(*fdf).map);
	event_project(keycode, &(*fdf).map, &(*fdf).vec);
	put_pixel_about_map(&(*fdf).img, &(*fdf).map, &(*fdf).vec);
	mlx_put_image_to_window((*fdf).vars.mlx, (*fdf).vars.win, (*fdf).img.ptr, 0, 0);
	return (SUCCESS);
}
