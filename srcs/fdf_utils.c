/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:08:55 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/01 15:07:18 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	ft_clean_error(t_vector **vec, char **split_line, char *str)
{
	if (vec)
		all_clean((void **)vec);
	if (split_line)
		all_clean((void **)split_line);
	ft_error(str);
}

int is_set(char *set, char c)
{
	if (!set)
		return (ERROR);
	while (*set)
	{
		if (*set == c)
			return (SUCCESS);
		set++;
	}
	return (ERROR);
}
