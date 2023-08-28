/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:32:46 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/24 19:31:35 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_angle(t_va *va)
{
	if (va->kleft == 1)
		va->pa += 0.7 * SPEED;
	if (va->kright == 1)
		va->pa -= 0.7 * SPEED;
	if (va->pa > 2 * PI)
		va->pa -= (2 * PI);
	if (va->pa < 0)
		va->pa += (2 * PI);
}

static void	move_pos(t_va *va, float *pxf, float *pyf)
{
	if (va->kq == 1)
	{
		*pxf += sin(va->pa) * SPEED;
		*pyf -= cos(va->pa) * SPEED;
	}
	if (va->kd == 1)
	{
		*pxf -= sin(va->pa) * SPEED;
		*pyf += cos(va->pa) * SPEED;
	}
	if (va->kup == 1 || va->kz == 1)
	{
		*pxf += cos(va->pa) * SPEED;
		*pyf += sin(va->pa) * SPEED;
	}
	if (va->kdown == 1 || va->ks == 1)
	{
		*pxf -= cos(va->pa) * SPEED;
		*pyf -= sin(va->pa) * SPEED;
	}
}

static void	pad_check_move(t_va *va, float pxf, float pyf)
{
	if (((va->map)[(int)(va->py)][(int)(pxf + PAD)]) == 0
		&& ((va->map)[(int)(va->py)][(int)(pxf - PAD)]) == 0
		&& ((va->map)[(int)(va->py + PAD)][(int)(pxf + PAD)]) == 0
		&& ((va->map)[(int)(va->py + PAD)][(int)(pxf - PAD)]) == 0
		&& ((va->map)[(int)(va->py - PAD)][(int)(pxf + PAD)]) == 0
		&& ((va->map)[(int)(va->py - PAD)][(int)(pxf - PAD)]) == 0)
		va->px = pxf;
	if (((va->map)[(int)(pyf + PAD)][(int)(va->px)]) == 0
		&& ((va->map)[(int)(pyf - PAD)][(int)(va->px)]) == 0
		&& ((va->map)[(int)(pyf + PAD)][(int)(va->px + PAD)]) == 0
		&& ((va->map)[(int)(pyf - PAD)][(int)(va->px + PAD)]) == 0
		&& ((va->map)[(int)(pyf + PAD)][(int)(va->px - PAD)]) == 0
		&& ((va->map)[(int)(pyf - PAD)][(int)(va->px - PAD)]) == 0)
		va->py = pyf;
}

static void	init_img_black(t_va *va)
{
	int	i;
	int	j;

	i = 0;
	while (i < va->resx)
	{
		j = 0;
		while (j < va->resy)
		{
			my_mlx_pixel_put(va, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

int	key_move(t_va *va)
{
	float	pxf;
	float	pyf;

	pxf = va->px;
	pyf = va->py;
	move_angle(va);
	move_pos(va, &pxf, &pyf);
	pad_check_move(va, pxf, pyf);
	init_img_black(va);
	dessin_sol(va);
	dessin_plafond(va);
	cast_rays(va);
	if (va->kmap)
	{
		draw_map(va);
		draw_player(va->px * va->map_q,
			va->py * va->map_q, va);
		draw_dir(va->px * va->map_q,
			va->py * va->map_q, va);
	}
	mlx_put_image_to_window(va->mlx, va->win, va->img, 0, 0);
	return (0);
}
