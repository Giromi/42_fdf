/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:23:20 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/25 22:31:33 by minsuki2         ###   ########.fr       */
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

void all_clean(void **object)
{
	int i;

	if (!object)
		return ;
	i = 0;
	while (object[i])
		free(object[i++]);
	free(object);
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
	while (++(*h))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		*w = 0;
		priv_w = *w;
		while (split_line[(*w)++])
			;
		if (priv_w && priv_w != *w)
			return (ERROR);
		all_clean((void **)split_line);
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
	*split_line = ft_split(line, ' ');
	free(line);
	return (SUCCESS);
}

char *ft_problem(t_point **vector, char **split_line)
{
	if (vector)
		all_clean((void **)vector);
	if (split_line)
		all_clean((void **)split_line);
	exit(1);
}

void	input_point_val(t_point ***vector, char **split_line, t_space *map)
{
	map->w = 0;
	while (split_line[map->w])
	{
		(*vector)[map->h][map->w].init.xi = map->w;
		(*vector)[map->h][map->w].init.yi = map->h;
		(*vector)[map->h][map->w].init.zi = ft_atoi(split_line[map->w]);
		map->w++;
	}
}
/* check_vector 함수
 * : malloc을 하기 위해서는 row값이 몇개인 지 알 수 있어야 한다.
 *
 */
t_point	**check_map(char *file, t_space *map)
{
	t_point	**vector;
	int		fd;
	char	**split_line;

	if (!file || get_row(file, &map->h, &map->w) == ERROR)
		return (NULL);
	vector = (t_point **)malloc(sizeof(t_point *) * map->h);
	if (vector == NULL)
		return (NULL);
	vector[map->h - 1] = NULL;
	fd = open(file, O_RDONLY);
	map->h = 0;
	while (line_to_split(fd, &split_line) == SUCCESS)
	{
		vector[map->h] = (t_point *)malloc(sizeof(t_point) * map->w);
		if (!vector[map->h])
			ft_problem(vector, split_line);
		input_point_val(&vector, split_line, map);
		all_clean((void **)split_line);
		map->h++;
	}
	close(fd);
	return (vector);
}


int main(int ac, char *av[])
{
	atexit(only_exit);
	t_space		map;
	t_point		**vector;
	t_vars		vars;
	t_data		image;
	/* int			color; */

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

	if (ac < 2)
	{
		perror("ERROR");
		return (ERROR);
	}
	vector = check_map(av[1], &map);
	if (!vector)
	{
		perror("file is empty");
		return (ERROR);
	}



	/* zoom_in_out(&vector, &map, 1); */
	initializing_map(&vector, &map);
	write_map_pixel(&vector, map, &image)
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			printf("x = %f, y = %f, z = %f\n", vector[i][j].final.xf, vector[i][j].final.yf, vector[i][j].final.zf);
			my_mlx_pixel_put(&image, vector[i][j].final.xf, vector[i][j].final.yf, RGB_GREEN);
		}
		printf("\n");
	}
	/* my_mlx_pixel_put(&image, WIDTH / 2, HEIGHT / 2, RGB_GREEN); */
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	all_clean((void **)vector);
	return (SUCCESS);
}



/* scale * x */

/* scale = 35; */
/* scale -= 0.9; */

