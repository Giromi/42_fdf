/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_translation_scale.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:43:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/25 02:18:25 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

 // esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	} return (0);
}

int exit_hook()
{
	exit(0);
}

 //원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << (8 * 3) | r << (8 * 2) | g << (8 * 1) | b << (8 * 0));
}


int main(void)
{
	t_vars	vars;
	t_data	image;
	int		i;
	int		j;
	int		scale;

	int img_width = WIDTH;
	int img_height = HEIGHT;
	int map[11][20] ={{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					  { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					  { 0,  0, 10, 10,  0,  0, 10, 10,  0,  0,  0, 10, 10, 10, 10, 10,  0,  0,  0},
					  { 0,  0, 10, 10,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0,  0, 10, 10,  0,  0},
					  { 0,  0, 10, 10,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0,  0, 10, 10,  0,  0},
					  { 0,  0, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0, 10, 10, 10, 10,  0,  0,  0},
					  { 0,  0,  0, 10, 10, 10, 10, 10,  0,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0},
					  { 0,  0,  0,  0,  0,  0, 10, 10,  0,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0},
					  { 0,  0,  0,  0,  0,  0, 10, 10,  0,  0,  0, 10, 10, 10, 10, 10, 10,  0,  0},
					  { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
					  { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}};


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
	my_mlx_pixel_put(&image, (double)WIDTH / 2, (double)HEIGHT / 2, 0x00FF0000);
	(void)map;
	i = 0;
	scale = 80;
	while (i < 20 * scale)
	{
		j = 0;
		while (j < 11 * scale)
		{
			// Translation 이동: 원점 더하기
			my_mlx_pixel_put(&image, i + (double)WIDTH / 2 - scale * (20 / 2), j + (double)HEIGHT / 2 - scale * (11 / 2), 0x00FFFFFF);
			i - i 
			j += scale;
		}
		i += scale;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}

