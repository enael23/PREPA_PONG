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

int	ft_rainbow(double f)
{
	int color;

	if (f <= 0.2)
		color = 0x00000000 + ((int)(f * 5 * 255) << 16);
	else if (f <= 0.4)
		color = 0x00FF0000 + ((int)((f - 0.2) * 5 * 255) << 8);
	else if (f <= 0.6)
		color = 0x00FFFF00 - ((int)((f - 0.4) * 5 * 255) << 16);
	else if (f <= 0.8)
		color = 0x0000FF00 + ((int)((f - 0.6) * 5 * 255));
	else
		color = 0x0000FFFF - ((int)((f - 0.8) * 5 * 255) << 8);
	return (color);
}

/* blanc jaune rouge noir */

int	ft_wyrb(double f)
{
	int color;

	if (f <= (1 / 3.))
		color = 0x00FFFFFF - ((int)(f * 3. * 255));
	else if (f <= (2 / 3.))
		color = 0x00FFFF00 - ((int)((f - (1. / 3.)) * 3. * 255) << 8);
	else
		color = 0x00FF0000 - ((int)((f - (2. / 3.)) * 3. * 255) << 16);
return (color);
}

int	ft_wbrbbwrb(double f)
{
	int color;

	if (f <= (1 / 7.)) /* bleu -> blanc */
		color = 0x000000FF + ((int)(f * 7. * 255) << 8) + ((int)(f * 7. * 255) << 16);
	else if (f <= (2 / 7.)) /* blanc -> rouge */
		color = 0x00FFFFFF - ((int)((f - (1. / 7.)) * 7. * 255) << 8) 
			- ((int)((f - (1. / 7.)) * 7. * 255));
	else if (f <= (3 / 7.)) /* rouge -> noir */
		color = 0x00FF0000 - ((int)((f - (2. / 7.)) * 7. * 255) << 16);
	else if (f <= (4 / 7.)) /* noir -> bleu */
		color = 0x00000000 + ((int)((f - (3. / 7.)) * 7. * 255));
	else if (f <= (5 / 7.)) /* bleu -> blanc */
		color = 0x000000FF + ((int)((f - (4. / 7.)) * 7. * 255) << 8) 
			+ ((int)((f - (4. / 7.)) * 7. * 255) << 16);
	else if (f <= (6 / 7.)) /* blanc -> rouge */
		color = 0x00FFFFFF - ((int)((f - (5. / 7.)) * 7. * 255) << 8) 
			- ((int)((f - (5. / 7.)) * 7. * 255));
	else /* rouge -> noir */
		color = 0x00FF0000 - ((int)((f - (6. / 7.)) * 7. * 255) << 16);
	return (color);
}

/* JULIA */
void	draw_julia(t_va *va)
{
	int i = 0;
	int j = 0;
	int	iter;
	double	Re;
	double	Im;
	double	oldRe;
	double	oldIm;
	double	degrad;
	
	while (i < va->win_x)
	{
		j = 0;
		while (j < va->win_y)
		{
			Re = ((i - va->i0) / va->zoom)/300;
			Im = ((j - va->j0) / va->zoom)/300;
			iter = 0;
			while (++iter < va->max_it)
			{
				oldRe = Re;
				oldIm = Im;
				Re = oldRe * oldRe - oldIm * oldIm + va->cRe;
				Im = 2 * oldRe * oldIm + va->cIm;
				if ((Re * Re + Im * Im) > 4)
					break;
			}
			degrad = 1.0 * iter / va->max_it;
		//	my_mlx_pixel_put(&(va->img), i, j, ft_rainbow(degrad));
			my_mlx_pixel_put(&(va->img), i, j, (va->palet)[va->palet_nbr](degrad));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(va->mlx, va->win, va->img.img, 0, 0);
}

/* MANDELBROT */
void	draw_mandel(t_va *va)
{
	int i = 0;
	int j = 0;
	int	iter;
	double	Re;
	double	Im;
	double	oldRe;
	double	oldIm;
	double	cRe;
	double	cIm;
	double	degrad;
	
	while (i < va->win_x)
	{
		j = 0;
		while (j < va->win_y)
		{
			cRe = ((i - va->i0) / va->zoom)/300;
			cIm = ((j - va->j0) / va->zoom)/300;
			Re = 0.;
			Im = 0.;
			iter = 0;
			while (++iter < va->max_it)
			{
				oldRe = Re;
				oldIm = Im;
				Re = oldRe * oldRe - oldIm * oldIm + cRe;
				Im = 2 * oldRe * oldIm + cIm;
				if ((Re * Re + Im * Im) > 4)
					break;
			}
			degrad = 1.0 * iter / va->max_it;
			my_mlx_pixel_put(&(va->img), i, j, (va->palet)[va->palet_nbr](degrad));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(va->mlx, va->win, va->img.img, 0, 0);
}


double ft_absdbl(double a)
{
	if (a < 0)
		a = -a;
	return (a);
}

/*  BURNING SHIP */
void	draw_burn(t_va *va)
{
	int i = 0;
	int j = 0;
	int	iter;
	double	Re;
	double	Im;
	double	oldRe;
	double	oldIm;
	double	cRe;
	double	cIm;
	double	degrad;
	
	while (i < va->win_x)
	{
		j = 0;
		while (j < va->win_y)
		{
			cRe = ((i - va->i0) / va->zoom)/300;
			cIm = ((j - va->j0) / va->zoom)/300;
			Re = 0.;
			Im = 0.;
			iter = 0;
			while (++iter < va->max_it)
			{
				oldRe = Re;
				oldIm = Im;
				Re = oldRe * oldRe - oldIm * oldIm + cRe;
				Im = 2 * ft_absdbl(oldRe * oldIm) + cIm;
				if ((Re * Re + Im * Im) > 4)
					break;
			}
			degrad = 1.0 * iter / va->max_it;
			my_mlx_pixel_put(&(va->img), i, j, (va->palet)[va->palet_nbr](degrad));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(va->mlx, va->win, va->img.img, 0, 0);
}


int				mouse_hook(int button, int x, int y, t_va *va)
{
	if (button == 1)
	{
		va->i0 -= (x - (va->win_x / 2));
		va->j0 -= (y - (va->win_y / 2));
	}
	else if (button == 5)
	{
		va->zoom *= 2;
		va->i0 -= (x - (va->i0));
		va->j0 -= (y - (va->j0));
	}
	else if (button == 4)
	{
		va->zoom /= 2;
		va->i0 += (x - (va->i0)) / 2;
		va->j0 += (y - (va->j0)) / 2;
	}
	va->draw(va);
	return (0);
}

void	print_infos(t_va *va)
{
	printf("Max_IT = %d, zoom = x%.2f, x = %.2f, y = %.2f, palet = %d\n", va->max_it, va->zoom,
			(va->i0 - va->win_x / 2), (va->i0 - va->win_x / 2), va->palet_nbr);
}

int             key_hook(int keycode, t_va *va)
{
printf("KEYCODE = %d\n", keycode);	
	if (keycode == 65307)
		ft_close(va);
	else if (keycode == 116)
		va->max_it += 50;
	else if (keycode == 103 && va->max_it > 50)
		va->max_it -= 50;	
	else if (keycode == 124 || keycode == 65363)
		va->i0 -= 100;
    else if (keycode == 123 || keycode == 65361)
		va->i0 += 100;
    else if (keycode == 126 || keycode == 65362)
		va->j0 += 100;
    else if (keycode == 125 || keycode == 65364)
		va->j0 -= 100;
	else if (keycode == 119)
	{
		va->zoom *= 2;
		va->i0 -= ((va->win_x / 2) - (va->i0));
		va->j0 -= ((va->win_y / 2) - (va->j0));
	}
	else if (keycode == 115)
	{
		va->zoom /= 2;
		va->i0 += ((va->win_x / 2) - (va->i0)) / 2;
		va->j0 += ((va->win_y / 2) - (va->j0)) / 2;
	}
	else if (keycode == 32)
	{
		if (va->palet_nbr < 2)
			(va->palet_nbr)++;
		else
			va->palet_nbr = 0;
	}
	else if (keycode == 99)
		va->set_c = !(va->set_c);
	else if (keycode == 65307)
		ft_close(va);
	print_infos(va);
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
    va->win = mlx_new_window(va->mlx, va->win_x, va->win_y, "Fractol Explorer");
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
	(va->palet)[0] = ft_rainbow;
	(va->palet)[1] = ft_wyrb;
	(va->palet)[2] = ft_wbrbbwrb;
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
