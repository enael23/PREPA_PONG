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

# define PI 3.1415926535
# define SPEED 5
# define FPS 100.0

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
	int			score;
	double		ball_posx;
	double		ball_posy;
	double		ball_vx;
	double		ball_vy;
	double		ball_angle;
	int			ball_speed;



	t_data		img;

	unsigned long prev_time;
	unsigned long current_time;
	double delta_time;
	double target_frame_time;

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

	int x = 10;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 100)
		{
			if ((va->player_pos - 50 + j) < va->win_y)
				// my_mlx_pixel_put(va, va->win_x - 2 + i, y - 2 + j, 0x00FF0000);
				mlx_pixel_put(va->mlx, va->win, x - 2 + i, va->player_pos - 50 + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_ball(t_va *va)
{
	int	i;
	int	j;

	int x = floor(va->ball_posx);
	int y = floor(va->ball_posy);

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((x - 5 + i) > 0 && (x - 5 + i) < va->win_x
				&& (y - 5 + i) > 0 && (y - 5 + i) < va->win_y)
				// my_mlx_pixel_put(va, va->win_x - 2 + i, y - 2 + j, 0x00FF0000);
				mlx_pixel_put(va->mlx, va->win, x - 5 + i, y - 5 + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void uptdate_game(t_va *va)
{
	if (va->kup && va->player_pos > 50)
		va->player_pos -= 10;
	if (va->kdown && va->player_pos < va->win_y - 50)
		va->player_pos += 10;

	int out = 0;
	if (va->ball_posx < 10)
		out = 1;

	va->ball_posx += va->ball_vx;
	va->ball_posy += va->ball_vy;

	//CONTACT
	if (va->ball_posx <= 10 && !out
			&& va->ball_posy > (va->player_pos - 50)
			&& va->ball_posy < (va->player_pos + 50))
	{
		va->ball_vx = -va->ball_vx * 1.2;
		va->ball_vy *= 1.2;
		++va->score;
	}

	if (va->ball_posx >= va->win_x)
		va->ball_vx = -va->ball_vx;
	if (va->ball_posy <= 0 || va->ball_posy >= va->win_y)
		va->ball_vy = -va->ball_vy;

	if (va->ball_posx <= 0 &&
			(va->ball_posy < (va->player_pos - 50)
			|| va->ball_posy > (va->player_pos + 50)))
	{
		va->ball_posx = va->win_x / 2;
		va->ball_posy = va->win_y / 2;
		
		va->ball_vx = va->ball_speed * sin(va->ball_angle);
		va->ball_vy = va->ball_speed * cos(va->ball_angle);

		printf("SCORE : %d\n", va->score);
		va->score = 0;
	}



	// mlx_clear_window(va->mlx, va->win);
	// draw_player(va);
}

int game_loop(t_va *va)
{
		va->current_time = get_time_us();
		va->delta_time += (va->current_time - va->prev_time) / 1000000.0;
		va->prev_time =  va->current_time;

		while (va->delta_time >= va->target_frame_time)
		{
			uptdate_game(va);
			va->delta_time -= va->target_frame_time;

			mlx_clear_window(va->mlx, va->win);
			draw_player(va);
			draw_ball(va);
		}

		// mlx_clear_window(va->mlx, va->win);
		// draw_player(va);
		return(0);
}

void	init_va(t_va *va)
{
	va->win_x = 600;
	va->win_y = 600;
    va->mlx = mlx_init();
    va->win = mlx_new_window(va->mlx, va->win_x, va->win_y, "Pong Arena");

	va->kup = 0;
	va->kdown = 0;
	va->player_pos = va->win_y / 2;
	va->score = 0;
//	va->kleft = 0;
//	va->kright = 0;
//	va->set_c = 0;
//	va->palet_nbr = 0;

	va->ball_angle = PI / 3;
	va->ball_speed = SPEED;

	va->ball_posx = va->win_x / 2;
	va->ball_posy = va->win_y / 2;
	va->ball_vx = va->ball_speed * sin(va->ball_angle);
	va->ball_vy = va->ball_speed * cos(va->ball_angle);
	


	va->prev_time = get_time_us();
	va->delta_time = 0.0;
	va->target_frame_time = 1.0 / FPS; // 50 FPS


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
	
	mlx_hook(va.win, 2, 1L << 0, key_press, &va);
	mlx_loop_hook(va.mlx, game_loop, &va);
	mlx_hook(va.win, 3, 1L << 1, key_release, &va);
	mlx_hook(va.win, 33, 1L << 17, ft_close, &va);
	mlx_loop(va.mlx);

	// mlx_key_hook(va.win, key_press, &va);
	// mlx_key_hook(va.win, key_release, &va);

	// unsigned long prev_time = get_time_us();
	// unsigned long current_time;
	// double delta_time = 0.0;
	// const double target_frame_time = 1.0 / 2.0; // 2 FPS

	// while (1)
	// {
	// 	current_time = get_time_us();
	// 	delta_time += (current_time - prev_time) / 1000000.0;
	// 	prev_time =  current_time;

	// 	while (delta_time >= target_frame_time)
	// 	{
	// 		uptdate_game(&va);
	// 		delta_time -= target_frame_time;
	// 	}

	// 	mlx_clear_window(va.mlx, va.win);
	// 	draw_player(&va);
	// 	// mlx_flush_image(va.mlx, va.win);
	// }
	
	
	return (0);
} 
