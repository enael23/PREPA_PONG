/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 04:46:33 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/23 20:06:11 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_va *va, int x, int y, int color)
{
	char	*dst;

	dst = va->addr + (y * va->line_length + x * (va->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	key_press_map(int keycode, t_va *va)
{
	if (keycode == 65289)
	{
		if (va->kmap == 0)
			va->kmap++;
		else
			va->kmap = 0;
	}
}

int	key_press(int keycode, t_va *va)
{
	if (keycode == 65307)
		clean_exit(va);
	if (keycode == 115 || keycode == 1)
		va->ks = 1;
	if (keycode == 97 || keycode == 113 || keycode == 0)
		va->kq = 1;
	if (keycode == 122 || keycode == 119 || keycode == 13)
		va->kz = 1;
	if (keycode == 100 || keycode == 2)
		va->kd = 1;
	if (keycode == 124 || keycode == 65363)
		va->kleft = 1;
	if (keycode == 123 || keycode == 65361)
		va->kright = 1;
	if (keycode == 126 || keycode == 65362)
		va->kup = 1;
	if (keycode == 125 || keycode == 65364)
		va->kdown = 1;
	key_press_map(keycode, va);
	return (0);
}

int	key_release(int keycode, t_va *va)
{
	if (keycode == 115 || keycode == 1)
		va->ks = 0;
	if (keycode == 97 || keycode == 113 || keycode == 0)
		va->kq = 0;
	if (keycode == 122 || keycode == 119 || keycode == 13)
		va->kz = 0;
	if (keycode == 100 || keycode == 2)
		va->kd = 0;
	if (keycode == 124 || keycode == 65363)
		va->kleft = 0;
	if (keycode == 123 || keycode == 65361)
		va->kright = 0;
	if (keycode == 126 || keycode == 65362)
		va->kup = 0;
	if (keycode == 125 || keycode == 65364)
		va->kdown = 0;
	return (0);
}

void	engine(t_va *va)
{
	mlx_hook(va->win, 2, 1L << 0, key_press, va);
	mlx_loop_hook(va->mlx, key_move, va);
	mlx_hook(va->win, 3, 1L << 1, key_release, va);
	mlx_hook(va->win, 33, 1L << 17, clean_exit, va);
	mlx_loop(va->mlx);
}
