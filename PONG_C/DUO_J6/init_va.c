/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_va.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:01:41 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/23 20:17:54 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_va2(t_va *va)
{
	va->px = 0;
	va->py = 0;
	va->pa = 0;
	va->kz = 0;
	va->kq = 0;
	va->ks = 0;
	va->kd = 0;
	va->kup = 0;
	va->kdown = 0;
	va->kleft = 0;
	va->kright = 0;
	va->kmap = 0;
	va->hit_h = 0;
	va->hit_v = 0;
	va->hit_p = 0;
	va->tnum = 0;
}

void	init_va(t_va *va)
{
	va->mlx = NULL;
	va->win = NULL;
	va->img = NULL;
	va->addr = NULL;
	va->bits_per_pixel = 0;
	va->line_length = 0;
	va->endian = 0;
	va->map = NULL;
	va->fcolor = 0;
	va->fcolor_status = 0;
	va->ccolor = 0;
	va->ccolor_status = 0;
	va->strtxt[0] = NULL;
	va->strtxt[1] = NULL;
	va->strtxt[2] = NULL;
	va->strtxt[3] = NULL;
	init_va2(va);
}
