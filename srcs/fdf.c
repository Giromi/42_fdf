/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:23:20 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/31 23:11:23 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * 파싱
 * vector
 * int xi <- 초기 x좌표
 * int yi <- 초기 y좌표
 * int zi <- 초기 z좌표
 * Rotation z_axis 45 degree
 * Rotation x_axis 35.749?
 * scale
 *
 * 점찍는거만 원점
 * 화면 나가지 않게
 * 직각 투영법
 * => x Rot(0, 0, 0)
 *         : 각도 변환 해줌 -> 오른손 나사법칙 코딩 (외적)
 *         ot(X, Y) 화면 방향
 */

#include "fdf.h"

void only_exit(void)
{
	system("leaks -q fdf");
}


/* void vector_clean(t_point **map) */
/* { */
	/* int i; */
	/* int j; */

	/* if (!vector) */
		/* return ; */
	/* i = 0; */
	/* while (vector[i]) */
		/* while(vector[i][j]) */
			/* free(vector[i][j]); */
	/* if (vector) */
		/* free(vector); */
/* } */

int get_row(const char *file, int *h, int *w)
{
	char	*line;
	int		fd;
	int		priv_w;
	char	**split_line;

	*h = 0;
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		*w = 0;
		priv_w = *w;
		while (split_line[(*w)])
			(*w)++;
		if (priv_w && priv_w != *w)
			return (ERROR);
		all_clean((void **)split_line);
		(*h)++;
	}
	close(fd);
	return (SUCCESS);
}

int	line_to_split(int fd, char ***split_line)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ERROR);
	/*
	 * map check 하는 함수 제작 요망
	 */

	*split_line = ft_split(line, ' ');
	free(line);
	return (SUCCESS);
}


static void	input_point_to_vector(t_vector ***vec, char **split, t_index *idx)
{
	int		num;

	(*idx).j = 0;
	while (split[(*idx).j])
	{
		num  = ft_atoi(split[(*idx).j]);
		/* if */
		(*vec)[(*idx).i][(*idx).j].zi = num;
		(*idx).j++;
	}
}
/* check_vector 함수
 * : malloc을 하기 위해서는 row값이 몇개인 지 알 수 있어야 한다.
 *
 */
t_vector	**check_map(char *file, t_space *map)
{
	t_vector	**vec;
	t_index		idx;
	int			fd;
	char		**split_line;

	if (!file || get_row(file, &(*map).info.h, &(*map).info.w) == ERROR)
		return (NULL);
	vec = (t_vector **)malloc(sizeof(t_vector *) * ((*map).info.h) + 1);
	if (vec == NULL)
		ft_problem(vec, NULL);
	vec[(*map).info.h] = NULL;
	fd = open(file, O_RDONLY);
	idx.i = 0;
	while (idx.i < (*map).info.h && line_to_split(fd, &split_line) == SUCCESS)
	{
		vec[idx.i] = (t_vector *)malloc(sizeof(t_vector) * ((*map).info.w));
		if (!vec[idx.i])
			ft_problem(vec, split_line);
		input_point_to_vector(&vec, split_line, &idx);
		all_clean((void **)split_line);
		idx.i++;
	}
	close(fd);
	return (vec);
}

void vector_check(t_vector ***vec);

int main(int ac, char *av[])
{
	atexit(only_exit);
	t_main		fdf;

	if (ac < 2)
	{
		perror("ERROR");
		return (ERROR);
	}
	fdf.vars.mlx = mlx_init();
	fdf.vars.win = mlx_new_window(fdf.vars.mlx, WIDTH, HEIGHT, "Hellow World!");
	fdf.img.ptr = NULL;
	setting_mlx_map(&fdf.vars, &fdf.img, &fdf.map);
	fdf.vec = check_map(av[1], &fdf.map);
	initializing_map(&fdf.map, &fdf.vec);
	rotate_vector(&fdf.map, &fdf.vec, rot_z_axis, ISO_ANGLE_Z_AXIS);
	rotate_vector(&fdf.map, &fdf.vec, rot_x_axis, ISO_ANGLE_X_AXIS);
	/* vector_check(&fdf.vec); */
	if (!fdf.vec)
	{
		exit_hook(&fdf);
		perror("file is empty");
		return (ERROR);
	}
	put_pixel_about_map(&fdf.img, &fdf.map, &fdf.vec);
	mlx_put_image_to_window(fdf.vars.mlx, fdf.vars.win, fdf.img.ptr, 0, 0);
	mlx_hook(fdf.vars.win, VAL_KEY_HOOK, 0, key_hook, &fdf);
	mlx_hook(fdf.vars.win, VAL_MOUSE_HOOK, 0, mouse_hook, &fdf);
	mlx_hook(fdf.vars.win, 17, 0, exit_hook, &fdf);
	mlx_loop(fdf.vars.mlx);
}




/* scale * x */

/* scale = 35; */
/* scale -= 0.9; */

void vector_check(t_vector ***vec)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			printf("%d%d x = %f, y = %f, z = %f, zi = %d\n", i, j, (*vec)[i][j].xf, (*vec)[i][j].yf, (*vec)[i][j].zf, (*vec)[i][j].zi);
		}
		printf("\n");
	}
}


/* void red_line() */
/* { */
	/* t_screen	cordi_debug; */
	/* for (int i = 0; i < 100; i++) */
	/* { */
		/* cordi_debug.xs = i; */
		/* cordi_debug.ys = 0; */
		/* my_mlx_pixel_put(&fdf.img, &fdf.map, &cordi_debug, 0x00FF0000); */
	/* } */
	/* for (int j = 0; j < 100; j++) */
	/* { */
		/* cordi_debug.xs = 0; */
		/* cordi_debug.ys = -j; */
		/* my_mlx_pixel_put(&fdf.img, &fdf.map, &cordi_debug, 0x00FF0000); */
	/* } */
/* } */

/* mlx_loop_hook(fdf.vars.mlx, &fdf_loop, &fdf); // 적들이 움직이게 하고 싶을 때 */
