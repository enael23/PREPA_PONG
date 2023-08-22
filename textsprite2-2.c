/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textsprite2-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:34:41 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/20 04:40:35 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535 

float px, py, dy, dy, pa, ra;
int kz, kq, ks, kd, kup, kdown, kleft, kright = 0;
float speed = 0.05;
float tampon = 0.2;
int	resx, resy, shdw;
float	ANGLE = 0.92;
float hitH, hitV, hitP;
int tnum;

typedef struct	s_txt {
	int		x;
	int		y;
	void	*img;
	char	*addr;
	int		bpp;
	int		lln;
	int		end;
} 				t_txt;

typedef struct	s_sprt {
	float	sx;
	float	sy;
	float	shit;
	float	dist;
}				t_sprt;

typedef struct  s_va {
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	void		*img2;
	char		*addr2;
	int			map[10][20];
/*	float		hitH;
	float		hitV;
	float		hitP:*/
	t_txt		txt[6];
//	int			tnum;
	t_sprt		sprt[10];
	int			sprtnb;
}				t_va;
/*
void	ft_swap(t_va *va)
{
	void *tmp;

	tmp = va->img;
	va->img = va->img2;
	va->img2 = tmp;
	tmp = va->addr;
	va->addr = va->addr2;
	va->addr2 = tmp;
}
*/

void            my_mlx_pixel_put(t_va *va, int x, int y, int color)
{
    char    *dst;

    dst = va->addr + (y * va->line_length + x * (va->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void init_img(t_va *va)
{
	int i = 0;
	int j = 0;
	while (i < 640)
	{
		j = 0;
		while (j < 480)
		{
			my_mlx_pixel_put(va, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

void			carre(int x, int y, t_va *va, int color)
{
	int xfin;
	int yfin;

	xfin = x + 24;
	yfin = y + 24;
	while (++x < (xfin))
	{
		y = yfin - 24;
		while (++y < yfin)
			my_mlx_pixel_put(va, x, y, color);
	}
}

void			drawmap(t_va *va, int map[10][20])
{
	int	i;
	int j;
	int color;

	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 20)
		{
			if (map[i][j] == 1)
				color = 0x00FFFFFF;
			if (map[i][j] == 0)
				color = 0x00303030;
			carre(j * 12, i * 12, va, color);
		}
	}
}

void dessin_carre(float x, float y, t_va *va)
{
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(va, x - 5 + i, y - 5 + j, 0x00FF0000 + x / 3);
			j++;
		}
		i++;
	}
}

void dessin_dir(float x, float y, float a, double len, t_va *va)
{
	int i = -1;
	while (++i < (len * 12) && (y + (i * sin(a)) > 0) && (y + (i * sin(a)) < 400) 
			&& (x + (i * cos(a)) > 0) && (x + (i * cos(a)) < 300)
			)
	{
		my_mlx_pixel_put(va, x + (i * cos(a)), y + (i * sin(a)), 0x0000FF00);
	}
}

double	ft_wallDistV(float px, float py, float pa, t_va *va)
{
	int dof;
	float	rx, ry,/* ra,*/ x0, y0;
	double 	aTan, wallDist;

	ra = pa;
	dof = 0;
	aTan = -1/tan(ra);
	if (ra > PI)
	{
		ry = (int)(py)-0.000001;
		rx = px + (py - ry) * aTan;
		y0 = -1;
		x0 = aTan;
	}
	if (ra < PI)
	{
		ry = (int)(py + 1);
		rx = px + (py - ry) * aTan;
		y0 = 1;
		x0 = -aTan;
	}
	if (ra == 0 || ra == PI)
	{
		rx = px + 100;
		ry = py + 100;
		dof = 20;
	}
/*regler max dof a mapx (taille horizontale de la carte)*/
	while (dof < 20 && ry < 10 && rx < 20 && rx >= 0 && ry >= 0)
	{
		if ((va->map)[(int)ry][(int)rx] == 1)
			dof = 20;
		else
		{
			if ((va->map)[(int)ry][(int)rx] == 2)
			{
				va->sprt[va->sprtnb].sx = (int)rx + 0.5;
				va->sprt[va->sprtnb].sy = (int)ry + 0.5;
				va->sprtnb += 1;
			}
			rx += x0;
			ry += y0;
			dof += 1;
		}
	}
	hitH = rx;
	wallDist = sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px));
	return (wallDist);
}

double	ft_wallDistH(float px, float py, float pa, t_va *va)
{
	int dof;
	float	rx, ry,/* ra,*/ x0, y0;
	double 	Tan, wallDist;

	ra = pa;
	dof = 0;
	Tan = tan(ra);
	if (ra > PI/2 && ra < 3*PI/2)
	{
		rx = (int)(px)-0.000001;
		ry = py + (rx - px) * Tan;
		x0 = -1;
		y0 = -Tan;
	}
	if (ra < PI/2 || ra > 3*PI/2)
	{
		rx = (int)(px + 1);
		ry = py + (rx - px) * Tan;
		x0 = 1;
		y0 = Tan;
	}
	if (ra == PI/2 || ra == 3*PI/2)
	{
		rx = px + 100;
		ry = py + 100;
		dof = 10;
	}
/*regler max dof a mapy (taille verticale de la carte)*/
	while (dof < 10 && ry < 10 && rx < 20 && ry >= 0 && rx >= 0)
	{
		if ((va->map)[(int)ry][(int)rx] == 1)
			dof = 10;
		else
		{
			if ((va->map)[(int)ry][(int)rx] == 2)
			{
				va->sprt[va->sprtnb].sx = (int)rx + 0.5;
				va->sprt[va->sprtnb].sy = (int)ry + 0.5;
				va->sprtnb += 1;
			}
			rx += x0;
			ry += y0;
			dof += 1;
		}
	}
	hitV = ry;
	wallDist = sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px));
	return (wallDist);
}

double	ft_min(float wdh, float wdv)
{
	shdw = 1;
	if (wdh > wdv)
	{	
		if ((ra < PI/2) || (ra > 3*PI/2))
		{
			hitP = hitV - (int)hitV;
			tnum = 0;
		}
		else
		{
			hitP = 1 - (hitV - (int)hitV);
			tnum = 1;
		}
		return(wdv);
	}
	shdw = 0;
	if (ra > PI)
	{
		hitP = hitH - (int)hitH;
		tnum = 2;
	}
	else
	{
		hitP = 1 - (hitH - (int)hitH);
		tnum = 3;
	}
	return(wdh);
}

int             key_press(int keycode, t_va *va)
{
	(void)va;
	if (keycode == 122 || keycode == 1)
		ks = 1;
	if (keycode == 113 || keycode == 0)
		kq = 1;
	if (keycode == 115 || keycode == 13)
		kz = 1;
	if (keycode == 100 || keycode == 2)
		kd = 1;
	if (keycode == 124 || keycode == 65363)
		kleft = 1;
	if (keycode == 123 || keycode == 65361)
		kright = 1;
	if (keycode == 126 || keycode == 65362)
		kup = 1;
	if (keycode == 125 || keycode == 65364)
		kdown = 1;
	
	return (0);
}

int             key_release(int keycode, t_va *va)
{
	(void)va;
	if (keycode == 122 || keycode == 1)
		ks = 0;
	if (keycode == 113 || keycode == 0) 
		kq = 0;
	if (keycode == 115|| keycode == 13)
		kz = 0;
	if (keycode == 100|| keycode == 2)
		kd = 0;
	if (keycode == 124 || keycode == 65363)
		kleft = 0;
	if (keycode == 123 || keycode == 65361)
		kright = 0;
	if (keycode == 126 || keycode == 65362)
		kup = 0;
	if (keycode == 125 || keycode == 65364)
		kdown = 0;
	
	return (0);
}

void			dessin_sol(t_va *va)
{
	int x;
	int y;

	x = 0;
	y = resy / 2;

	while (y < resy)
	{
		x = 0;
		while (x < resx)
		{
			my_mlx_pixel_put(va, x + 240, y, 0x00888888);
			x++;
		}
		y++;
	}
}

void			dessin_plafond(t_va *va)
{
	int x;
	int y;

	x = 0;
	y = 0;

	while (y < resy / 2)
	{
		x = 0;
		while (x < resx)
		{
			my_mlx_pixel_put(va, x + 240, y, 0x00444444);
			x++;
		}
		y++;
	}
}
/*
void			dessin_mur(int N, float wallDist, float ra, t_va *va)
{
	float hmur;
	int y;

	hmur = resy - (wallDist * 10 * cos(ra));
	y = (resy / 2) - (hmur / 2);
	while (y < ((resy / 2) + (hmur / 2)))
		{
			my_mlx_pixel_put(va, N + 300, y, 0x00FF0000);
			y++;
		}
}*/

int         get_color(char *txtaddr, int txtbpp, int txtlln, int x, int y)
{
    int color;
    char *addr;

    addr = txtaddr + (y * txtlln + x * (txtbpp / 8));
    color = *(unsigned int*)addr;
//printf("x = %d, y = %d, color = %x\n", x, y, color);
    return(color);
}


int				shadow(int color, float dist)
{
	int t;
	int	r;
	int	g;
	int	b;
(void)dist;
	t = (color & (0xFF << 24)) >> 24;
	r = (color & (0xFF << 16)) >> 16;
	g = (color & (0xFF << 8)) >> 8;
	b = (color & 0xFF);
	r *= 1/(1+dist);
	g *= 1/(1+dist);
	b *= 1/(1+dist);
	return(t << 24 | r << 16 | g << 8 | b);
}

int             shadowdist(int color, float dist)
{
    int t;
    int r;
    int g;
    int b;
	float pow;

	pow = 0.5;
    t = (color & (0xFF << 24)) >> 24;
    r = (color & (0xFF << 16)) >> 16;
    g = (color & (0xFF << 8)) >> 8;
    b = (color & 0xFF);
	if (pow * dist > 1)
    {
		r /= pow*dist;
	    g /= pow*dist;
	    b /= pow*dist;
	}
    return(t << 24 | r << 16 | g << 8 | b);
}

void			dessin_mur(int N, float wallDist, float ra, t_va *va)
{
	float hmur;
	int pixcol;
	float y;

	hmur = resy / (wallDist * cos(ra));
//	if (hmur > resy)
//		hmur = resy;
	y = (resy / 2) - (hmur / 2);
	while (y < ((resy / 2) + (hmur / 2)))
	{
//		my_mlx_pixel_put(va, N + 300, y + 250, 0x00FF0000 - shdw * 0x00a10000);
		if ((y < resy) && (y > 0))
		{
//printf("N = %d, ra = %f, hmur = %f, y = %d, txty = %f\n", N, ra, hmur, y, va->txt.y * (y - ((resy /2) - (hmur / 2))) / hmur);
			pixcol = get_color(va->txt[tnum].addr, va->txt[tnum].bpp, va->txt[tnum].lln,
				hitP * va->txt[tnum].x,
				va->txt[tnum].y * (y - ((resy /2) - (hmur / 2))) / hmur);
		//	pixcol = shadow(pixcol, shdw);
			pixcol = shadowdist(pixcol, wallDist);
//printf("x= %d, y = %d, ra = %f\n", N+300, y+250, ra);
			my_mlx_pixel_put(va, N + 240, y, pixcol);
		}
		y++;
	}
}

float			FixAng(float ang)
{
	if (ang > 2 * PI)
		return(ang - 2 * PI);
	if (ang < 0)
		return(ang + 2 * PI);
	return(ang);
}

void			dessin_sky(t_va *va)
{
	float x;
	float y;
	float tx;
	float ty;
	float pixcol;

	y = 1;
	while (y < resy/2)
	{
		x = 1;
		while (x < resx)
		{
			tx = (ANGLE / (2 * PI) * (x / resx) + (pa / (2 * PI)));
			ty = y / (resy / 2);
			pixcol = get_color(va->txt[4].addr, va->txt[4].bpp, va->txt[4].lln,
				va->txt[4].x * tx,
				va->txt[4].y * ty);
//printf("x = %f, tx = %f, y = %f, ty = %f\n", x, tx, y, ty);
//printf("txtx = %d, txty = %d\n", va->txt[4].x, va->txt[4].y);
//printf("x = %f, y = %f\n", va->txt[4].x * tx, va->txt[4].y * ty); 
			my_mlx_pixel_put(va, x + 240, y + 250, pixcol);
			x++;
		}
		y++;
	}
}

void			dessin_floor_lodev(t_va *va)
{
	int x, y, pixcol;
	float tx, ty;

//int y;
//(void)va;

	y = resy;
	while (y-- >  resy/2)
	{
		int p = y - resy / 2;
		float posZ = 0.5 * resy;
		float rd = posZ / p;
		float floorStepX = -(2*tan(ANGLE/2)*rd) * sin(pa) / resx;
		float floorStepY = (2*tan(ANGLE/2)*rd) * cos(pa) / resx;
		float floorX = px + rd * cos(pa) + rd * tan(ANGLE/2) * cos(FixAng(PI / 2 - pa));
		float floorY = py + rd * sin(pa) - rd * tan(ANGLE/2) * sin(FixAng(PI / 2 - pa));
//printf("px=%f, py=%f, pa=%f, rd=%f, floorX=%f, floorY=%f\n", px, py, pa, rd, floorX, floorY);
//my_mlx_pixel_put(va, floorX * 24, floorY * 24, 0x00FF0000);

//		float floorStepX = rowDistance * cos(fixAng(pa + PI/2)) 
//		float floorX = posX + rowDistance * cos(fixAng(pa - ANGLE / 2));
//		float floorX = posX + rowDistance * sin(fixAng(pa - ANGLE / 2));
		
		x = 0;
		while(x < resx)
		{
			tx = floorX - (int)floorX;
			ty = floorY - (int)floorY;
			floorX += floorStepX;
			floorY += floorStepY;
			if ((y < resy) && (y > 0) && tx > 0 && ty > 0)
				{
//printf("floorY = %f, tx = %f, ty = %f\n", floorY, tx, ty);
//printf("BOB\n");
					pixcol = get_color(va->txt[2].addr, va->txt[2].bpp, va->txt[2].lln,
						tx * va->txt[2].x, ty * va->txt[2].y);
				//	pixcol = shadow(pixcol, shdw);
					pixcol = shadowdist(pixcol, rd);
//printf("x= %d, y = %d, ra = %f\n", x + 240, y+250, ra);
					my_mlx_pixel_put(va, x + 240, y + 250, pixcol);
				}
			x++;
		}
	}
}

void            dessin_mur2(int N, float wallDist, float ra, t_va *va)
{
    float hmur;
    int pixcol;
    float y/*, tx, ty*/;

    hmur = resy / (wallDist * cos(ra));
    y = (resy / 2) - (hmur / 2);
    while (y < ((resy / 2) + (hmur / 2)))
    {
    	if ((y < resy) && (y > 0))
		{
			pixcol = get_color(va->txt[tnum].addr, va->txt[tnum].bpp, va->txt[tnum].lln,
				hitP * va->txt[tnum].x,
				va->txt[tnum].y * (y - ((resy /2) - (hmur / 2))) / hmur);
		//	pixcol = shadow(pixcol, shdw);
			pixcol = shadowdist(pixcol, wallDist);
//printf("x= %d, y = %d, ra = %f\n", N+300, y+250, ra);
			my_mlx_pixel_put(va, N + 240, y + 250, pixcol);
		}
		y++;
	}
/*	
float	ny;
float	cosa = cos(pa);
float	sina = sin(pa);
//float	raFix=cos(FixAng(ra-pa));
y++;
	while (y < resy)
	{
		ny = (resy - y);
		tx = px + (((2 * wallDist / (resy - hmur)) * ny) + 1) * cosa;
		ty = py + (((2 * wallDist / (resy - hmur)) * ny) + 1) * sina;
//  		dy=y-(resy/2);
//		raFix=cos(FixAng(pa-ra));
//		tx = px / 2 + cosa * (resy / 2) / dy / raFix;
//		ty = py / 2 + sina * (resy / 2) / dy / raFix;

  		if ((y < resy) && (y > 0))
		{
			pixcol = get_color(va->txt[0].addr, va->txt[0].bpp, va->txt[0].lln,
				(tx - (int)tx) * va->txt[0].x, (ty - (int)ty) * va->txt[0].y);
			my_mlx_pixel_put(va, N + 240, y + 250, pixcol);
		}
		y++;
	}
*/
}

void			cptSprtDist(t_va *va)
{
	int		i;
	float	sa;
//float	bob;

	i = 0;
	while (i < va->sprtnb)
	{
		va->sprt[i].dist = sqrt((px - va->sprt[i].sx) * (px - va->sprt[i].sx) +
			(py - va->sprt[i].sy) * (py - va->sprt[i].sy));
//		sa = fabs(atan((py - va->sprt[i].sy)/(px - va->sprt[i].sx)));
		sa = atan((py - va->sprt[i].sy)/((px - va->sprt[i].sx)));
//bob = ((py - va->sprt[i].sy)/(px - va->sprt[i].sx));
//printf("bob = %f, sa = %f\n", bob, sa);
//if (sa < 0) 
//	sa += 2* PI;
		va->sprt[i].shit = (va->sprt[i].dist * cos(/*fabs*/(sa - pa))) *
			(tan(sa - pa) - tan(ra - pa));
		if ((px - va -> sprt[i].sx) < 0)
			va->sprt[i].shit *= -1;
		i++;
	}
}

void			swapSprt(t_sprt *a, t_sprt *b)
{
	t_sprt	keep;

	keep.sx = (*a).sx;
	keep.sy = (*a).sy;
	keep.dist = (*a).dist;
	keep.shit = (*a).shit;
	(*a).sx = (*b).sx;
	(*a).sy = (*b).sy;
	(*a).dist = (*b).dist;
	(*a).shit = (*b).shit;
	(*b).sx = keep.sx;
	(*b).sy = keep.sy;
	(*b).dist = keep.dist;
	(*b).shit = keep.shit;
}

void			srtSprt(t_va *va)
{
	int		n;
	int		check;

	n = 0;
	check = 0;
	while (check == 0)
	{
		check = 1;
		while (n < (va->sprtnb - 1))
		{
			if (va->sprt[n].dist > va->sprt[n + 1].dist)
			{
				swapSprt(&va->sprt[n], &va->sprt[n+1]);
				check = 0;
			}
			n++;
		}
		n = 0;
	}
}

void            dessin_sprites(int N, int i, float ra, t_va *va, float wallDist)
{
    float hmur;
    int pixcol;
    float y/*, tx, ty*/;
(void)ra;
    hmur = resy / (va->sprt[i].dist/* * cos(ra)*/);
    y = (resy / 2) - (hmur / 2);
    while (y < ((resy / 2) + (hmur / 2)))
    {
    	if ((y < resy) && (y > 0) && (va->sprt[i].shit < 0.5) && (va->sprt[i].shit > -0.5)
			&& va->sprt[i].dist < wallDist)
		{
			pixcol = get_color(va->txt[5].addr, va->txt[5].bpp, va->txt[5].lln,
				(va->sprt[i].shit + 0.5) * va->txt[5].x,
				va->txt[5].y * (y - ((resy /2) - (hmur / 2))) / hmur);
		//	pixcol = shadow(pixcol, shdw);
			if (pixcol != 0x00000000)
			{
				pixcol = shadowdist(pixcol, va->sprt[i].dist);
//printf("x= %d, y = %d, ra = %f\n", N+300, y+250, ra);
				my_mlx_pixel_put(va, N + 240, y + 250, pixcol);
			}
		}
		y++;
	}
}

void			mng_sprt(int N, float a, t_va *va, float wallDist)
{
	int i;

	cptSprtDist(va);
	srtSprt(va);
	i = va->sprtnb;

	while (--i >= 0)
	{
		dessin_sprites(N, i, a, va, wallDist);
	}
}


void			drawrays(float px, float py, float pa, t_va *va)
{
	int N;
	int i;
//	float ANGLE;
	float ra;
	float wallDist;


//	ANGLE = 0.92;
	N = resx;
	ra = pa - ANGLE / 2;
	i = -1;
	while (i++ < N)
	{
		if (ra > 2 * PI)
			ra -= (2 * PI);
		if (ra < 0)
			ra += (2 * PI);
		va->sprtnb = 0;
		wallDist = ft_min(ft_wallDistV(px, py, ra, va), ft_wallDistH(px, py, ra, va));
		dessin_dir(px*12, py*12, ra, wallDist, va);
		dessin_mur(i, wallDist, fabs(pa - ra), va);
		dessin_mur2(i, wallDist, fabs(pa - ra), va);
		mng_sprt(i, fabs(pa - ra), va, wallDist);
		ra += (ANGLE / (N - 1));
	}
}

void			dessin_texture(t_va *va)
{
	int x, y;
	
//	int txtx;
//	int txty;
//	void *txtmlx;
//	void *txtimg;


//	char        *txtaddr;
//	int         txtbpp;
//	int         txtlln;
//	int         txtend;

//	txtimg = mlx_xpm_file_to_image(va->mlx, "./textures/eagle.xpm", &txtx, &txty);
//printf("texture txtx = %d, txty = %d\n", txtx, txty);
//	txtaddr = mlx_get_data_addr(txtimg, &txtbpp, &txtlln, &txtend);
	
	x = 0;
	while (x < /*va->txt[4].x*2*/50)
		{
			y = 0;
			while (y < /*va->txt[4].y*2*/50)
			{
				my_mlx_pixel_put(va, x, y + 300, get_color(va->txt[5].addr, va->txt[5].bpp, 
					va->txt[5].lln, x/2, y/2));
				y++;
			}
			x++;
		}
}

int             key_move(t_va *va)
{
	float pxf = px;
	float pyf = py;

//	if (ks == 1)
//		pyf -= speed;
	if (kq == 1)
	{	
		pxf += sin(pa) * speed;
		pyf -= cos(pa) * speed;
	}
//		pxf -= speed;
//	if (kz == 1)
//		pyf += speed;
	if (kd == 1)
	{	
		pxf -= sin(pa) * speed;
		pyf += cos(pa) * speed;
	}
//		pxf += speed;
	if (kleft == 1)
		pa += 0.7 * speed;
	if (kright == 1)
		pa -= 0.7 * speed;
/*modif angle */
	if (pa > 2 * PI)
		pa -= (2 * PI);
	if (pa < 0)
		pa += (2 * PI);
	if (kup == 1 || kz == 1)
	{	
		pxf += cos(pa) * speed;
		pyf += sin(pa) * speed;
	}
	if (kdown == 1 || ks == 1)
	{	
		pxf -= cos(pa) * speed;
		pyf -= sin(pa) * speed;
	}
/*move after colision checks*/
	if (((va->map)[(int)(py)][(int)(pxf+tampon)]) == 0
			&& ((va->map)[(int)(py)][(int)(pxf-tampon)]) == 0
			&& ((va->map)[(int)(py+tampon)][(int)(pxf+tampon)]) == 0
			&& ((va->map)[(int)(py+tampon)][(int)(pxf-tampon)]) == 0
			&& ((va->map)[(int)(py-tampon)][(int)(pxf+tampon)]) == 0
			&& ((va->map)[(int)(py-tampon)][(int)(pxf-tampon)]) == 0)
		px = pxf;
	if (((va->map)[(int)(pyf+tampon)][(int)(px)]) == 0
			&& ((va->map)[(int)(pyf-tampon)][(int)(px)]) == 0
			&& ((va->map)[(int)(pyf+tampon)][(int)(px+tampon)]) == 0
			&& ((va->map)[(int)(pyf-tampon)][(int)(px+tampon)]) == 0
			&& ((va->map)[(int)(pyf+tampon)][(int)(px-tampon)]) == 0
			&& ((va->map)[(int)(pyf-tampon)][(int)(px-tampon)]) == 0)
		py = pyf;
	init_img(va);
	drawmap(va, va->map);
	dessin_carre(px*12, py*12, va);
//	dessin_dir(px*24, py*24, pa, wallDist, va);
	dessin_sol(va);
	dessin_plafond(va);
	dessin_sky(va);
	dessin_floor_lodev(va);
	drawrays(px, py, pa, va);

	dessin_texture(va);

	mlx_put_image_to_window(va->mlx, va->win, va->img, 0, 0);
//printf("px = %f, py = %f, pa = %f\n", px, py, pa);
	
	return (0);
}

int             main(void)
{
    t_va      va;

	int			toto[10][20] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	int i, j;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 20)
		{
			(va.map)[i][j] = toto[i][j];
		}
	}

	px = 1.5;
	py = 1.5;
	pa = 3 * PI / 2;

	resx = 400;
	resy = 240;

    va.mlx = mlx_init();
    va.win = mlx_new_window(va.mlx, 640, 480, "Hello world!");

    va.img = mlx_new_image(va.mlx, 740, 580);
	va.addr = mlx_get_data_addr(va.img, &va.bits_per_pixel, &va.line_length, &va.endian);
//	va.img2 = mlx_new_image(va.mlx, 740, 580);
//	va.addr2 = mlx_get_data_addr(va.img2, &va.bits_per_pixel, &va.line_length, &va.endian);

va.txt[0].img = mlx_xpm_file_to_image(va.mlx, "./textures/eagle.xpm", &va.txt[0].x, &va.txt[0].y);
va.txt[0].addr = mlx_get_data_addr(va.txt[0].img, &va.txt[0].bpp, &va.txt[0].lln, &va.txt[0].end);
va.txt[1].img = mlx_xpm_file_to_image(va.mlx, "./textures/red.xpm", &va.txt[1].x, &va.txt[1].y);
va.txt[1].addr = mlx_get_data_addr(va.txt[1].img, &va.txt[1].bpp, &va.txt[1].lln, &va.txt[1].end);
va.txt[2].img = mlx_xpm_file_to_image(va.mlx, "./textures/greystone.xpm", &va.txt[2].x, &va.txt[2].y);
va.txt[2].addr = mlx_get_data_addr(va.txt[2].img, &va.txt[2].bpp, &va.txt[2].lln, &va.txt[2].end);
va.txt[3].img = mlx_xpm_file_to_image(va.mlx, "./textures/purplestone.xpm", &va.txt[3].x, &va.txt[3].y);
va.txt[3].addr = mlx_get_data_addr(va.txt[3].img, &va.txt[3].bpp, &va.txt[3].lln, &va.txt[3].end);
va.txt[4].img = mlx_xpm_file_to_image(va.mlx, "./textures/skybox2.xpm", &va.txt[4].x, &va.txt[4].y);
va.txt[4].addr = mlx_get_data_addr(va.txt[4].img, &va.txt[4].bpp, &va.txt[4].lln, &va.txt[4].end);
va.txt[5].img = mlx_xpm_file_to_image(va.mlx, "./textures/tonneau.xpm", &va.txt[5].x, &va.txt[5].y);
va.txt[5].addr = mlx_get_data_addr(va.txt[5].img, &va.txt[5].bpp, &va.txt[5].lln, &va.txt[5].end);

	mlx_hook(va.win, 2, 1L<<0, key_press, &va);
	mlx_loop_hook(va.mlx, key_move, &va);
	mlx_hook(va.win, 3, 1L<<1, key_release, &va);
    mlx_loop(va.mlx);
	return (0);


} 
