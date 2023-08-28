/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:54:21 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/24 19:36:05 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_ratio(t_va *va)
{
	int	tmp;

	if (va->xmap > va->ymap)
		tmp = va->xmap;
	else
		tmp = va->xmap;
	if (tmp < 100)
		va->map_q = 300 / tmp;
	else if (tmp < 250)
		va->map_q = 500 / tmp;
	else
		va->map_q = 2;
}

void	carre(int x, int y, t_va *va, int color)
{
	int	xfin;
	int	yfin;

	xfin = x + va->map_q;
	yfin = y + va->map_q;
	while (++x < (xfin))
	{
		y = yfin - va->map_q;
		while (++y < yfin)
		{
			if (x < va->resx && y < va->resy)
				my_mlx_pixel_put(va, x, y, color);
		}
	}
}

void	draw_player(float x, float y, t_va *va)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((x - 2 + i) < va->resx && (y - 2 + j) < va->resy)
				my_mlx_pixel_put(va, x - 2 + i, y - 2 + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	draw_map(t_va *va)
{
	int	i;
	int	j;
	int	color;

	j = -1;
	while (++j < va->ymap)
	{
		i = -1;
		while (++i < va->xmap)
		{
			if (va->map[j][i] == 0)
			{
				color = 0x00FFFFFF;
				carre(i * va->map_q, j * va->map_q, va, color);
			}
		}
	}
}

void	draw_dir(float x, float y, t_va *va)
{
	int		i;
	float	a;

	a = va->pa;
	i = -1;
	while (++i < (va->map_q) && (y + (i * sin(a)) > 0)
		&& (y + (i * sin(a)) < va->resy)
		&& (x + (i * cos(a)) > 0) && (x + (i * cos(a)) < va->resx))
	{
		my_mlx_pixel_put(va, x + (i * cos(a)), y + (i * sin(a)), 0x00FF0000);
	}
}
