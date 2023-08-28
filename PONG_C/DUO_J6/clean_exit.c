/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:15:35 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/23 19:17:31 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	clean_exit(t_va *va)
{
	free(va->strtxt[0]);
	free(va->strtxt[1]);
	free(va->strtxt[2]);
	free(va->strtxt[3]);
	ft_freesplit(va->map);
	if (va->txt[0].img)
		mlx_destroy_image(va->mlx, va->txt[0].img);
	if (va->txt[1].img)
		mlx_destroy_image(va->mlx, va->txt[1].img);
	if (va->txt[2].img)
		mlx_destroy_image(va->mlx, va->txt[2].img);
	if (va->txt[3].img)
		mlx_destroy_image(va->mlx, va->txt[3].img);
	if (va->img)
		mlx_destroy_image(va->mlx, va->img);
	if (va->win)
		mlx_destroy_window(va->mlx, va->win);
	if (va->mlx)
	{
		mlx_destroy_display(va->mlx);
		free(va->mlx);
	}
	exit (0);
}
