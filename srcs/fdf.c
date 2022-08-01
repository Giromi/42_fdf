/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:23:20 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 15:11:18 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_hook(t_main *fdf)
{
	all_clean((void **)(*fdf).vec);
	mlx_clear_window((*fdf).vars.mlx, (*fdf).vars.win);
	mlx_destroy_image((*fdf).vars.mlx, (*fdf).img.ptr);
	mlx_destroy_window((*fdf).vars.mlx, (*fdf).vars.win);
	exit(0);
}

int	line_to_split(int fd, char ***split_line)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ERROR);
	*split_line = ft_split(line, ' ');
	free(line);
	return (SUCCESS);
}

void	initializing_map(t_space *map, t_vector ***vec)
{
	t_index	idx;

	if (!map || !vec)
		return ;
	ft_bzero(&(*map).angle, sizeof(t_angle));
	(*map).base.xs = X_ORIGIN;
	(*map).base.ys = Y_ORIGIN;
	(*map).scale = (*map).init_scale;
	idx.i = 0;
	while (idx.i < (*map).info.h)
	{
		idx.j = 0;
		while (idx.j < (*map).info.w)
		{
			(*vec)[idx.i][idx.j].xf = idx.j - (*map).info.w / 2;
			(*vec)[idx.i][idx.j].yf = idx.i - (*map).info.h / 2;
			(*vec)[idx.i][idx.j].zf = (*vec)[idx.i][idx.j].zi;
			idx.j++;
		}
		idx.i++;
	}
}

static void	check_args(int ac, char **av)
{
	int	i;

	if (ac != 2)
		ft_error("wrong arguments");
	i = 0;
	while (av[1][i] != '.')
	{
		if (av[1][i] == '\0')
			ft_error("wrong file");
		i++;
	}
	if (ft_strncmp(av[1] + i, ".fdf\0", 5) != 0)
		ft_error("wrong name");
}

int	main(int ac, char *av[])
{
	t_main		fdf;

	check_args(ac, av);
	fdf.vec = check_map(av[1], &fdf.map);
	if (!fdf.vec)
		ft_error("map empty!");
	fdf.vars.mlx = mlx_init();
	fdf.vars.win = mlx_new_window(fdf.vars.mlx, WIDTH, HEIGHT, "fdf");
	fdf.img.ptr = NULL;
	fdf.map.init_scale = 1;
	initializing_map(&fdf.map, &fdf.vec);
	rotate_vector(&fdf.map, &fdf.vec, rot_z_axis, ISO_ANGLE_Z_AXIS);
	rotate_vector(&fdf.map, &fdf.vec, rot_x_axis, ISO_ANGLE_X_AXIS);
	key_hook(-1, &fdf);
	while ((fdf.map.max.xs < WIDTH - 100) && (fdf.map.max.ys < HEIGHT - 100)
		&& (fdf.map.min.xs > 100) && (fdf.map.min.ys > 100))
		mouse_hook(VAL_MOU_HEEL_UP, 0, 0, &fdf);
	fdf.map.init_scale = fdf.map.scale;
	key_hook(-1, &fdf);
	mlx_hook(fdf.vars.win, VAL_KEY_HOOK, 0, key_hook, &fdf);
	mlx_hook(fdf.vars.win, VAL_MOUSE_HOOK, 0, mouse_hook, &fdf);
	mlx_hook(fdf.vars.win, VAL_EXIT_HOOK, 0, exit_hook, &fdf);
	mlx_loop(fdf.vars.mlx);
}
