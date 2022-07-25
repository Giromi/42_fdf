/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exmaple_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:05:56 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/24 17:46:17 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

// mlx 구조체 mlx 포인터와 생성할 win 포인터를 가지고 있다.
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
	}
	return (0);
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
	/* int		color; */

	int img_width = 1920;
	int img_height = 1080;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
	/* for (int i = 0 ; i < 500 ; i++) */
	/* { */
		/* for (int j = 0 ; j < 500 ; j++) */
		/* { */
			/* double r = (double)(img_width - j) / (img_width - 1); */
			/* double g = (double)(i) / (img_height - 1); */
			/* double b = 1; */
			/* [> color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b)); <] */
			/* color = create_trgb(0, 255.999 * r, 255.999 * g, 255.999 * b); */
		/* } */
	/* } */
	my_mlx_pixel_put(&image, img_width / 2, img_height / 2, 0x00FFFFFF);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}

			/* mlx_pixel_put (mlx, win, i, j, 0x00FFFFFF); */
int get_t(int trgb)
{
  return (trgb & (0xFF << 24));
}

int get_r(int trgb)
{
  return (trgb & (0xFF << 16));
}

int get_g(int trgb)
{
  return (trgb & (0xFF << 8));
}

int get_b(int trgb)
{
  return (trgb & 0xFF);
}
