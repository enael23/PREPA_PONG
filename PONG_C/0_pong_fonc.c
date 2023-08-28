/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_fonc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 03:04:44 by jpauline          #+#    #+#             */
/*   Updated: 2021/09/15 03:51:59 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_va {
    void        *mlx;
    void        *win;
	int			win_x;
	int			win_y;
	double		i0;
	double		j0;
	int			max_it;
	double		cRe;
	double		cIm;
	double		zoom;
	int			kup;
	int			kdown;
	int			kleft;
	int			kright;
	int			palet_nbr;
	int			set_c;
	int			(*palet[4])();
	void		(*draw)();
	t_data		img;
}               t_va;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	ft_close(t_va *va)
{
	if (va->img.img)
		mlx_destroy_image(va->mlx, va->img.img);
	if (va->win)
		mlx_destroy_window(va->mlx, va->win);
	if (va->mlx)
	{
		mlx_destroy_display(va->mlx);
		free(va->mlx);
	}
	exit(0);
}


int             key_hook(int keycode, t_va *va)
{
printf("KEYCODE = %d\n", keycode);	
	if (keycode == 65307)
		ft_close(va);
	else if (keycode == 65307)
		ft_close(va);
	//print_infos(va);
	va->draw(va);
    return (0);
}

int             motion_notif(int x, int y, t_va *va)
{
	if (va->set_c && va->draw == draw_julia)
	{
		va->cRe = ((x - va->i0) / va->zoom)/300;
		va->cIm = ((y - va->j0) / va->zoom)/300;
		va->draw(va);
	}
	return (0);
}

void	init_va(t_va *va)
{
	va->win_x = 600;
	va->win_y = 600;
    va->mlx = mlx_init();
    va->win = mlx_new_window(va->mlx, va->win_x, va->win_y, "Pong Arena");
	va->i0 = va->win_x / 2;
	va->j0 = va->win_y / 2;
	va->max_it = 300;
	va->cRe = -0.7;
	va->cIm = 0.27015;
	va->zoom = 1;
	va->kup = 0;
	va->kdown = 0;
	va->kleft = 0;
	va->kright = 0;
	va->set_c = 0;
	va->palet_nbr = 0;

	va->img.img = mlx_new_image(va->mlx, va->win_x, va->win_y);
    va->img.addr = mlx_get_data_addr(va->img.img, &(va->img.bits_per_pixel), &(va->img.line_length), &(va->img.endian));
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i]) && (s2[i]) && (s1[i] == s2[i]))
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

int             main(int ac, char **av)
{
    t_va      va;

	init_va(&va);    
	if (ac != 2)
		ft_close(&va);
	if (ft_strcmp(av[1], "mandelbrot") == 0)
		va.draw = draw_mandel;
	else if (ft_strcmp(av[1], "julia") == 0)
		va.draw = draw_julia;
	else if (ft_strcmp(av[1], "burningship") == 0)
		va.draw = draw_burn;
	else 
		ft_close(&va);
	if (va.draw == NULL)
		ft_close(&va);

	va.draw(&va);
	mlx_key_hook(va.win, key_hook, &va);
	mlx_mouse_hook(va.win, mouse_hook, &va);
    mlx_hook(va.win, 6, 1L<<6, motion_notif, &va);
	mlx_hook(va.win, 33, 1L << 17, ft_close, &va);
    mlx_loop(va.mlx);
	return (0);
} 
