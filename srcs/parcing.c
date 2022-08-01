/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:10:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 20:45:51 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static ssize_t	read_file(const char *file)
{
	ssize_t	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("read fail");
	return (fd);
}

static int	ft_word_cnt(const char *line, char *set)
{
	int	i;
	int	width;

	if (!set)
		return (ERROR);
	i = 0;
	width = 0;
	while (*line)
	{
		if (!is_set(set, *line) && line++)
			continue ;
		width++;
		while (*line && is_set(set, *line) == ERROR)
			line++;
	}
	return (width);
}

static void	get_row(const char *file, int *h, int *w)
{
	char		*line;
	ssize_t		fd;

	fd = read_file(file);
	*h = 0;
	line = get_next_line(fd);
	if (!line)
		ft_error("empty map");
	*w = ft_word_cnt(line, " \t\n");
	while (line)
	{
		if (*w != ft_word_cnt(line, " \t\n"))
			ft_error("wrong map");
		(*h)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	input_point_to_vector(t_space *map, t_vector ***vec, char **split
		, t_index *idx)
{
	int		num;

	(*idx).j = 0;
	while ((*idx).j < (*map).info.w)
	{
		num = ft_atoi(split[(*idx).j]);
		if ((*split[(*idx).j] == '-' && num > 0)
			&& (*split[(*idx).j] != '-' && num < 0))
			ft_clean_error(*vec, split, "wrong num");
		(*vec)[(*idx).i][(*idx).j].zi = num;
		(*idx).j++;
	}
}

t_vector	**check_map(char *file, t_space *map)
{
	t_vector	**vec;
	t_index		idx;
	ssize_t		fd;
	char		**split_line;

	get_row(file, &(*map).info.h, &(*map).info.w);
	fd = read_file(file);
	vec = (t_vector **)malloc(sizeof(t_vector *) * ((*map).info.h + 1));
	if (vec == NULL)
		ft_clean_error(vec, NULL, "height malloc failed");
	vec[(*map).info.h] = NULL;
	idx.i = 0;
	while (idx.i < (*map).info.h && line_to_split(fd, &split_line) == SUCCESS)
	{
		vec[idx.i] = (t_vector *)malloc(sizeof(t_vector) * ((*map).info.w));
		if (!vec[idx.i])
			ft_clean_error(vec, split_line, "width malloc failed");
		input_point_to_vector(map, &vec, split_line, &idx);
		all_clean((void **)split_line);
		idx.i++;
	}
	close(fd);
	return (vec);
}
