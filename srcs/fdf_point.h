/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_point.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:17:12 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/25 22:49:11 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_POINT_H
# define FDF_POINT_H

typedef struct s_init
{
	int	xi;
	int	yi;
	int	zi;
}	t_init;

typedef struct s_final
{
	double xf;
	double yf;
	double zf;
}	t_final;

typedef struct s_screen
{
	double xs;
	double ys;
}	t_screen;

typedef struct s_point
{
	t_init		init;
	t_final		final;
	t_screen	screen;
}	t_point;


#endif
