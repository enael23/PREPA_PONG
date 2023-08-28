/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:43:18 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/23 20:18:26 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dessin_sol(t_va *va)
{
	int	x;
	int	y;

	x = 0;
	y = va->resy / 2;
	while (y < va->resy)
	{
		x = 0;
		while (x < va->resx)
		{
			my_mlx_pixel_put(va, x, y, va->fcolor);
			x++;
		}
		y++;
	}
}

void	dessin_plafond(t_va *va)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < va->resy / 2)
	{
		x = 0;
		while (x < va->resx)
		{
			my_mlx_pixel_put(va, x, y, va->ccolor);
			x++;
		}
		y++;
	}
}

static int	get_txt_color(t_txt txt, int x, int y)
{
	int		color;
	char	*addr;

	addr = txt.addr + (y * txt.lln + x * (txt.bpp / 8));
	color = *(unsigned int *)addr;
	return (color);
}

static void	dessin_mur(int n, float wallDist, float ra, t_va *va)
{
	float	hmur;
	float	y;
	int		pixcol;

	hmur = va->resy / (wallDist * cos(ra));
	y = (va->resy / 2) - (hmur / 2);
	while (y < ((va->resy / 2) + (hmur / 2)))
	{
		if ((y < va->resy) && (y > 0))
		{
			pixcol = get_txt_color(va->txt[va->tnum],
					va->hit_p * va->txt[va->tnum].x,
					va->txt[va->tnum].y
					* (y - ((va->resy / 2) - (hmur / 2))) / hmur);
			if (n > 0)
				my_mlx_pixel_put(va, n - 1, y, pixcol);
		}
		y++;
	}
}

void	cast_rays(t_va *va)
{
	int		n;
	int		i;
	float	ra;
	float	walldist;

	n = va->resx;
	ra = va->pa - ANGLE / 2;
	i = -1;
	while (i++ < n)
	{
		if (ra > 2 * PI)
			ra -= (2 * PI);
		if (ra < 0)
			ra += (2 * PI);
		walldist = ft_min(ft_walldistv(ra, va), ft_walldisth(ra, va), ra, va);
		dessin_mur(i, walldist, fabs(va->pa - ra), va);
		ra += (ANGLE / (n - 1));
	}
}
