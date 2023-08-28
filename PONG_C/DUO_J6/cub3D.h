/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:53:23 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 19:22:44 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# define PI 3.1415926535
# define SPEED 0.05
# define PAD 0.2
# define ANGLE 0.92

typedef struct s_txt
{
	int		x;
	int		y;
	void	*img;
	char	*addr;
	int		bpp;
	int		lln;
	int		end;
}	t_txt;

typedef struct s_sprt {
	float	sx;
	float	sy;
	float	shit;
	float	dist;
}	t_sprt;

typedef struct s_wd
{
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	x0;
	float	y0;
	double	tanr;
	double	atanr;
	double	walldist;
}	t_wd;

typedef struct s_va {
	int		resx;
	int		resy;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
	int		xmap;
	int		ymap;
	int		map_q;
	char	*strtxt[4];
	int		fcolor;
	int		fcolor_status;
	int		ccolor;
	int		ccolor_status;
	t_txt	txt[4];
	float	px;
	float	py;
	float	pa;
	int		kz;
	int		kq;
	int		ks;
	int		kd;
	int		kup;
	int		kdown;
	int		kleft;
	int		kright;
	int		kmap;
	float	hit_h;
	float	hit_v;
	float	hit_p;
	int		tnum;
	float	walldist;
}	t_va;

int		parsing(char *map, t_va *va);
void	init_va(t_va *va);
int		get_strtxt(char *line, int num, t_va *va);
int		get_colors(char *line, t_va *va);
int		is_map(char *line);
int		parse_map(char *line, int fd, t_va *va);
int		isempty_line(char *line);
int		get_rectangle(t_va *va);
int		check_map(char **map);
int		clean_exit(t_va *va);
void	engine(t_va *va);
int		key_move(t_va *va);
int		key_press(int keycode, t_va *va);
int		key_release(int keycode, t_va *va);
void	my_mlx_pixel_put(t_va *va, int x, int y, int color);
void	dessin_sol(t_va *va);
void	dessin_plafond(t_va *va);
void	cast_rays(t_va *va);
double	ft_walldistv(float a, t_va *va);
double	ft_walldisth(float a, t_va *va);
double	ft_min(float wdh, float wdv, float ra, t_va *va);
void	draw_map(t_va *va);
void	draw_player(float x, float y, t_va *va);
void	draw_dir(float x, float y, t_va *va);
int		name_file(char *str);
void	map_ratio(t_va *va);

#endif
