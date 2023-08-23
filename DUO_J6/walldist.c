/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walldist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:46:09 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/24 19:46:58 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_walldistv2(t_va *va, t_wd *wd)
{
	if (wd->ra > PI)
	{
		wd->ry = (int)(va->py) - 0.0001;
		wd->rx = va->px + (va->py - wd->ry) * wd->atanr;
		wd->y0 = -1;
		wd->x0 = wd->atanr;
	}
	if (wd->ra < PI)
	{
		wd->ry = (int)(va->py + 1);
		wd->rx = va->px + (va->py - wd->ry) * wd->atanr;
		wd->y0 = 1;
		wd->x0 = -wd->atanr;
	}
	if (wd->ra == 0 || wd->ra == PI)
	{
		wd->rx = va->px + 2 * va->xmap;
		wd->ry = va->py + 2 * va->ymap;
		wd->dof = va->ymap;
	}
}

double	ft_walldistv(float a, t_va *va)
{
	t_wd	wd;

	wd.ra = a;
	wd.dof = 0;
	wd.atanr = -1 / tan(wd.ra);
	ft_walldistv2(va, &wd);
	while (wd.dof < va->ymap && wd.ry < va->ymap
		&& wd.rx < va->xmap && wd.rx >= 0 && wd.ry >= 0)
	{
		if ((va->map)[(int)wd.ry][(int)wd.rx] == 1)
			wd.dof = va->ymap;
		else
		{
			wd.rx += wd.x0;
			wd.ry += wd.y0;
			wd.dof += 1;
		}
	}
	va->hit_h = wd.rx;
	wd.walldist = sqrt((wd.ry - va->py) * (wd.ry - va->py)
			+ (wd.rx - va->px) * (wd.rx - va->px));
	return (wd.walldist);
}

static void	ft_walldisth2(t_va *va, t_wd *wd)
{
	if (wd->ra > (PI / 2) && wd->ra < (3 * PI / 2))
	{
		wd->rx = (int)(va->px) - 0.0001;
		wd->ry = va->py + (wd->rx - va->px) * wd->tanr;
		wd->x0 = -1;
		wd->y0 = -wd->tanr;
	}
	if (wd->ra < (PI / 2) || wd->ra > (3 * PI / 2))
	{
		wd->rx = (int)(va->px + 1);
		wd->ry = va->py + (wd->rx - va->px) * wd->tanr;
		wd->x0 = 1;
		wd->y0 = wd->tanr;
	}
	if (wd->ra == (PI / 2) || wd->ra == (3 * PI / 2))
	{
		wd->rx = va->px + 2 * va->xmap;
		wd->ry = va->py + 2 * va->ymap;
		wd->dof = va->xmap;
	}
}

double	ft_walldisth(float a, t_va *va)
{
	t_wd	wd;

	wd.ra = a;
	wd.dof = 0;
	wd.tanr = tan(wd.ra);
	ft_walldisth2(va, &wd);
	while (wd.dof < va->xmap && wd.ry < va->ymap
		&& wd.rx < va->xmap && wd.ry >= 0 && wd.rx >= 0)
	{
		if ((va->map)[(int)wd.ry][(int)wd.rx] == 1)
			wd.dof = va->xmap;
		else
		{
			wd.rx += wd.x0;
			wd.ry += wd.y0;
			wd.dof += 1;
		}
	}
	va->hit_v = wd.ry;
	wd.walldist = sqrt((wd.ry - va->py) * (wd.ry - va->py)
			+ (wd.rx - va->px) * (wd.rx - va->px));
	return (wd.walldist);
}

double	ft_min(float wdh, float wdv, float ra, t_va *va)
{
	if (wdh > wdv)
	{
		if ((ra < PI / 2) || (ra > 3 * PI / 2))
		{
			va->hit_p = va->hit_v - (int)va->hit_v;
			va->tnum = 3;
		}
		else
		{
			va->hit_p = 1 - (va->hit_v - (int)va->hit_v);
			va->tnum = 2;
		}
		return (wdv);
	}
	if (ra > PI)
	{
		va->hit_p = va->hit_h - (int)va->hit_h;
		va->tnum = 0;
	}
	else
	{
		va->hit_p = 1 - (va->hit_h - (int)va->hit_h);
		va->tnum = 1;
	}
	return (wdh);
}
