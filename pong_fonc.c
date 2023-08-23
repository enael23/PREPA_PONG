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
#include <sys/time.h>

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

	int			kup;
	int			kdown;
	// int			kleft;
	// int			kright;
	int			player_pos;

	t_data		img;
}               t_va;

unsigned long get_time_us()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (unsigned long)tv.tv_sec * 1000000 + tv.tv_usec;
}

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


// int             key_hook(int keycode, t_va *va)
// {
// printf("KEYCODE = %d\n", keycode);	
// 	if (keycode == 65307)
// 		ft_close(va);
// 	else if (keycode == 65307)
// 		ft_close(va);
// 	//print_infos(va);
// 	va->draw(va);
//     return (0);
// }

// int             motion_notif(int x, int y, t_va *va)
// {
// 	if (va->set_c && va->draw == draw_julia)
// 	{
// 		va->cRe = ((x - va->i0) / va->zoom)/300;
// 		va->cIm = ((y - va->j0) / va->zoom)/300;
// 		va->draw(va);
// 	}
// 	return (0);
// }

int	key_press(int keycode, t_va *va)
{
	if (keycode == 65307)
		ft_close(va);
		// clean_exit(va);
	// if (keycode == 115 || keycode == 1)
	// 	va->ks = 1;
	// if (keycode == 97 || keycode == 113 || keycode == 0)
	// 	va->kq = 1;
	// if (keycode == 122 || keycode == 119 || keycode == 13)
	// 	va->kz = 1;
	// if (keycode == 100 || keycode == 2)
	// 	va->kd = 1;
	// if (keycode == 124 || keycode == 65363)
	// 	va->kleft = 1;
	// if (keycode == 123 || keycode == 65361)
	// 	va->kright = 1;
	if (keycode == 126 || keycode == 65362)
		va->kup = 1;
	if (keycode == 125 || keycode == 65364)
		va->kdown = 1;
	// key_press_map(keycode, va);
	return (0);
}

int	key_release(int keycode, t_va *va)
{
	// if (keycode == 115 || keycode == 1)
	// 	va->ks = 0;
	// if (keycode == 97 || keycode == 113 || keycode == 0)
	// 	va->kq = 0;
	// if (keycode == 122 || keycode == 119 || keycode == 13)
	// 	va->kz = 0;
	// if (keycode == 100 || keycode == 2)
	// 	va->kd = 0;
	// if (keycode == 124 || keycode == 65363)
	// 	va->kleft = 0;
	// if (keycode == 123 || keycode == 65361)
	// 	va->kright = 0;
	if (keycode == 126 || keycode == 65362)
		va->kup = 0;
	if (keycode == 125 || keycode == 65364)
		va->kdown = 0;
	return (0);
}

// void	engine(t_va *va)
// {
// 	mlx_hook(va->win, 2, 1L << 0, key_press, va);
// 	mlx_loop_hook(va->mlx, key_move, va);
// 	mlx_hook(va->win, 3, 1L << 1, key_release, va);
// 	mlx_hook(va->win, 33, 1L << 17, clean_exit, va);
// 	mlx_loop(va->mlx);
// }

void	draw_player(t_va *va)
{
	int	i;
	int	j;

	int y = 10;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((va->player_pos - 2 + i) < va->win_x && (y - 2 + j) < va->win_y)
				// my_mlx_pixel_put(va, va->win_x - 2 + i, y - 2 + j, 0x00FF0000);
				mlx_pixel_put(va->mlx, va->win, va->player_pos - 2 + i, y - 2 + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void uptdate_game(t_va *va)
{
	if (va->kup)
		va->player_pos += 10;
	if (va->kdown)
		va->player_pos -= 10;
	
	mlx_clear_window(va->mlx, va->win);
	draw_player(va);
}

void	init_va(t_va *va)
{
	va->win_x = 600;
	va->win_y = 600;
    va->mlx = mlx_init();
    va->win = mlx_new_window(va->mlx, va->win_x, va->win_y, "Pong Arena");

	va->kup = 0;
	va->kdown = 0;
	va->player_pos = va->win_x / 2;
//	va->kleft = 0;
//	va->kright = 0;
//	va->set_c = 0;
//	va->palet_nbr = 0;

	va->img.img = mlx_new_image(va->mlx, va->win_x, va->win_y);
    va->img.addr = mlx_get_data_addr(va->img.img, &(va->img.bits_per_pixel), &(va->img.line_length), &(va->img.endian));
}

int             main(int ac, char **av)
{
	(void)ac;
	(void)av;
    t_va      va;

	init_va(&va);    
	// if (va.draw == NULL)
	// 	ft_close(&va);

	// va.draw(&va);
	// mlx_key_hook(va.win, key_hook, &va);
	// mlx_mouse_hook(va.win, mouse_hook, &va);
    // mlx_hook(va.win, 6, 1L<<6, motion_notif, &va);
	// mlx_hook(va.win, 33, 1L << 17, ft_close, &va);
    // mlx_loop(va.mlx);
	
	// mlx_hook(va.win, 2, 1L << 0, key_press, &va);
	// mlx_loop_hook(va->mlx, key_move, va);
	// mlx_hook(va.win, 3, 1L << 1, key_release, &va);
	// mlx_hook(va.win, 33, 1L << 17, ft_close, &va);

	mlx_key_hook(va.win, key_press, &va);
	mlx_key_hook(va.win, key_release, &va);

	unsigned long prev_time = get_time_us();
	unsigned long current_time;
	double delta_time = 0.0;
	const double target_frame_time = 1.0 / 2.0; // 2 FPS

	while (1)
	{
		current_time = get_time_us();
		delta_time += (current_time - prev_time) / 1000000.0;
		prev_time =  current_time;

		while (delta_time >= target_frame_time)
		{
			uptdate_game(&va);
			delta_time -= target_frame_time;
		}

		// mlx_clear_window(va.mlx, va.win);
		// draw_player(&va);
		// mlx_flush_image(va.mlx, va.win);
	}
	
	
	return (0);
} 
