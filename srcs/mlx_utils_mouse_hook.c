/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_mouse_hook.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:07 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/31 23:39:00 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// esc key press event
static void event_zoom(int button, t_space *map)
{
	if (button == VAL_MOU_HEEL_UP && (*map).scale < 10000000)
		(*map).scale += (*map).scale * 0.1;
	else if (button == VAL_MOU_HEEL_DOWN && (*map).scale > 0.0001)
		(*map).scale -= (*map).scale * 0.1;
}

int	mouse_hook(int button, int x, int y, t_main *fdf)
{
	(void)x;
	(void)y;
	setting_mlx_map(&(*fdf).vars, &(*fdf).img, &(*fdf).map);
	event_zoom(button, &(*fdf).map);
	redraw(&(*fdf).vars, &(*fdf).img, &(*fdf).map, &(*fdf).vec);
	return (0);
}


void	setting_mlx_map(t_graphic *vars, t_image *img, t_space *map)
{
	if ((*img).ptr)
		mlx_destroy_image((*vars).mlx, (*img).ptr);
	if ((*vars).win)
		mlx_clear_window((*vars).mlx, (*vars).win);
	 // 이미지 객체 생성
	(*img).ptr = mlx_new_image((*vars).mlx, WIDTH, HEIGHT);
	 // 이미지 주소 할당
	(*img).addr = mlx_get_data_addr((*img).ptr , &(*img).bits_per_pixel
			, &(*img).line_length, &(*img).endian);
	(void)map;
}
	/* mlx_clear_window((*fdf).vars.mlx, (*fdf).vars.win); */

//원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void	my_mlx_pixel_put(t_image *img, t_screen *p1, int color)
{
	char	*dst;

	if (((*p1).xs < 0 || (*p1).xs > WIDTH)
			|| (((*p1).ys < 0 || (*p1).ys > HEIGHT)))
		return ;
	dst = img->addr + ((*p1).ys * img->line_length
			+ (*p1).xs * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int exit_hook(t_main *fdf)
{
	all_clean((void **)(*fdf).vec);
	mlx_clear_window((*fdf).vars.mlx, (*fdf).vars.win);
	mlx_destroy_image((*fdf).vars.mlx, (*fdf).img.ptr);
	mlx_destroy_window((*fdf).vars.mlx, (*fdf).vars.win);
	exit(0);
}
