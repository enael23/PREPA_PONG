/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:31:36 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 19:23:12 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	modifmap(t_va *va)
{
	int	i;
	int	j;

	i = 0;
	while (va->map[0][i])
		i++;
	va->xmap = i;
	i = 0;
	while (va->map[i])
		i++;
	va->ymap = i;
	j = 0;
	while (j < va->ymap)
	{
		i = -1;
		while (++i < va->xmap)
			va->map[j][i] -= '0';
		j++;
	}
}

static void	free_va(t_va *va)
{
	int	i;

	i = 0;
	while (va->map && va->map[i])
		free(va->map[i++]);
	if (va->map)
		free(va->map);
	i = 0;
	while (i < 4)
	{
		if (va->strtxt && va->strtxt[i])
			free(va->strtxt[i]);
		i++;
	}
}

static int	init_engine(t_va *va)
{
	va->mlx = mlx_init();
	if (!va->mlx)
		return (1);
	va->win = mlx_new_window(va->mlx, va->resx, va->resy, "Cub3D - MJ");
	if (!va->win)
		return (1);
	va->img = mlx_new_image(va->mlx, va->resx, va->resy);
	if (!va->img)
		return (1);
	va->addr = mlx_get_data_addr(va->img, &(va->bits_per_pixel),
			&(va->line_length), &(va->endian));
	if (!va->addr)
		return (1);
	return (0);
}

static int	load_textures(t_va *va)
{
	va->txt[0].img = mlx_xpm_file_to_image(va->mlx, va->strtxt[0],
			&(va->txt[0].x), &(va->txt[0].y));
	va->txt[1].img = mlx_xpm_file_to_image(va->mlx, va->strtxt[1],
			&(va->txt[1].x), &(va->txt[1].y));
	va->txt[2].img = mlx_xpm_file_to_image(va->mlx, va->strtxt[2],
			&(va->txt[2].x), &(va->txt[2].y));
	va->txt[3].img = mlx_xpm_file_to_image(va->mlx, va->strtxt[3],
			&(va->txt[3].x), &(va->txt[3].y));
	if (!va->txt[0].img || !va->txt[1].img || !va->txt[2].img
		|| !va->txt[3].img)
		return (1);
	va->txt[0].addr = mlx_get_data_addr(va->txt[0].img, &(va->txt[0].bpp),
			&(va->txt[0].lln), &(va->txt[0].end));
	va->txt[1].addr = mlx_get_data_addr(va->txt[1].img, &(va->txt[1].bpp),
			&(va->txt[1].lln), &(va->txt[1].end));
	va->txt[2].addr = mlx_get_data_addr(va->txt[2].img, &(va->txt[2].bpp),
			&(va->txt[2].lln), &(va->txt[2].end));
	va->txt[3].addr = mlx_get_data_addr(va->txt[3].img, &(va->txt[3].bpp),
			&(va->txt[3].lln), &(va->txt[3].end));
	if (!va->txt[0].addr || !va->txt[1].addr || !va->txt[2].addr
		|| !va->txt[3].addr)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_va	va;

	if (ac != 2)
		return (write(2, "Wrong argument number\n", 22), 1);
	init_va(&va);
	if (name_file(av[1]) || parsing(av[1], &va) || !va.map || !va.strtxt[0]
		|| !va.strtxt[1] || !va.strtxt[2] || !va.strtxt[3])
		return (write(2, "Error: data file corrupted\n", 27), free_va(&va), 1);
	modifmap(&va);
	va.resx = 800;
	va.resy = 600;
	if (init_engine(&va))
	{
		write(2, "engine init error\n", 22);
		clean_exit(&va);
	}
	if (load_textures(&va))
	{
		write(2, "texture loading error\n", 22);
		clean_exit(&va);
	}
	map_ratio(&va);
	engine(&va);
	return (0);
}
