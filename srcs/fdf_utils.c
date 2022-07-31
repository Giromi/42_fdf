/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:08:55 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/31 23:28:46 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void initializing_map(t_space *map, t_vector ***vec)
{
	t_index	idx;

	if (!map || !vec)
		return ;
	(*map).base.xs = X_ORIGIN;
	(*map).base.ys = Y_ORIGIN;
	(*map).scale = 1;
	while ((*map).scale * (*map).info.w < WIDTH - 700
			&& (*map).scale * (*map).info.h < HEIGHT - 700)
		(*map).scale++;
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

void all_clean(void **object)
{
	int i;

	if (!object)
		return ;
	i = 0;
	while (object[i])
		free(object[i++]);
	if (object)
	free(object);
}

char *ft_problem(t_vector **vec, char **split_line)
{
	if (vec)
		all_clean((void **)vec);
	if (split_line)
		all_clean((void **)split_line);
	exit(1);
}
