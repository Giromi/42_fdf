#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
# define WIDTH			1920.0
# define HEIGHT			1080.0
# define X_BASE			960.0
# define Y_BASE			540.0

static void	rot_x_axis(int *y, int *z, double angle)
{
	int	y0;
	int	z0;

	y0 = *y;
	z0 = *z;
	*y = y0 * cos(angle) - (*z) * sin(angle);
	*z = y0 * sin(angle) - (*z) * cos(angle);
}

/*
static void	rotate_y(int *x, int *z, double angle)
{
	int	x0;

	x0 = *x;
	*x = x0 * cos(angle) + (*z) * sin(angle);
	*z = -x0 * sin(angle) + (*z) * cos(angle);
}
*/


static void	rot_z_axis(int *x, int *y, double angle)
{
	int	x0;
	int	y0;

	x0 = *x;
	y0 = *y;
	*x = x0 * cos(angle) - y0 * sin(angle);
	*y = x0 * sin(angle) + y0 * cos(angle);
}

void	euler_pixel(int x, int y, int z, void *mlx, void *win)
{
	rot_z_axis(&x, &y, (45 * (M_PI / 180)));
	rot_x_axis(&y, &z, ((90 - 35.264) * (M_PI / 180)));
	/* mlx_pixel_put(mlx, win, x + (WIDTH / 2), y + (HEIGHT / 2), 0xFFFFFF); */
	mlx_pixel_put(mlx, win, x + X_BASE, y + Y_BASE, 0xFFFFFF);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	int		map_size;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "test");

	for (int i = 0; i < 100; i++)
		mlx_pixel_put(mlx, win, i + WIDTH / 2, HEIGHT / 2, 0x00FF0000);
	for (int j = 0; j < 100; j++)
		mlx_pixel_put(mlx, win, WIDTH / 2, HEIGHT / 2 - j, 0x00FF0000);
	map_size = 50;

	euler_pixel(0 - map_size, 0 - map_size, 0 - map_size, mlx, win);
	euler_pixel(100 - map_size, 0 - map_size, 0 - map_size, mlx, win);
	euler_pixel(0 - map_size, 100 - map_size, 0 - map_size, mlx, win);
	euler_pixel(100 - map_size, 100 - map_size, 0 - map_size, mlx, win);
	euler_pixel(0, 0, 100, mlx, win);
	euler_pixel(100, 0, 100, mlx, win);
	euler_pixel(0, 100, 100, mlx, win);
	euler_pixel(100, 100, 100, mlx, win);
	mlx_loop(mlx);
}
