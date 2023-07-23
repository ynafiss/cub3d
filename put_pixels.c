/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 5023/07/12 22:57:02 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/23 15:37:30 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_one_pixel(t_mlx *var,int x, int y, int color)
{
	// if ((y * W + x) < W * H)
	if ((x < 0 && x > W ) && (y < 0 && y > H))
	{
		printf("x: %d   y: %d\n", x, y);
		return;
	}
	var->draw_image[y * W + x] = color;
}

void	put_all_pixel(t_mlx *var,int x, int color)
{
	if ((x < 0 && x > W ))
		return;
	while(x < W * H)
	{
		var->draw_image[x] = color;
		x++;
	}
}

void	draw_rect(t_mlx *var, int x, int y, int height, int width, int color)
{
    while(height < 50)
    {
        width = 0;
        while(width < 50)
        {
            put_one_pixel(var, x * 50 + width, y * 50 + height, color);
            width++;
        }
        height++;
    }
}
int    get_color_w(t_west *tex, int y, int x)
{
    char    *str;
    int        colore;

    if (y < 0 || y > H || x < 0 || x > W)
        return (0);
    str = tex->west_addr + ((int)(y) *tex->w_line_length)
        + ((int)(x) *(tex->w_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}

int    get_color_e(t_east *tex, int y, int x)
{
    char    *str;
    int        colore;

    if (y < 0 || y > H || x < 0 || x > W)
        return (0);
    str = tex->east_addr + ((int)(y) * tex->e_line_length)
        + ((int)(x) * (tex->e_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}


int    get_color_n(t_north *tex, int y, int x)
{
    char    *str;
    int        colore;

    if (y < 0 || y > H || x < 0 || x > W)
        return (0);
    str = tex->north_addr + ((int)(y) * tex->n_line_length)
        + ((int)(x) *(tex->n_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}

int    get_color_s(t_south *tex, int y, int x)
{
    char    *str;
    int        colore;

    if (x < 0 || x >= W || y < 0 || y >= H)
        return (0);
    str = tex->south_addr + ((int)(y) *tex->s_line_length)
        + ((int)(x) *(tex->s_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}

void draw_wall(double x, double y, double i, t_mlx *p, double angel, int verti)
{	
    // double	dest;
	double	wall_h;
	double	start;
	double	end;
	double	t_y;
	double	t_x;
	int		r;
	int		j;
	int color;

	r = 0;
	wall_h = (50 / (sqrt(pow((int)(x) - (int)p->x_p, 2) + pow((int)(y) - (int)p->y_p, 2)) * cos(angel - p->angle)))
			* ((W / 2) / tan(FOV / 2));
	t_y = 0;
	j = 0;
	start = (H / 2) - (wall_h / 2);
	if (wall_h >= H){
		while (start < 0){
			start++;
		}
		j = (wall_h - H) / 2;
	}
	end = start + wall_h;
	if (end > H)
		end = H;
	if (verti == 1 && y <= p->y_p)
	{
		t_x = (x / 50 - (int)x / 50) * p->north.wight;
	}
	if (verti == 1 && y > p->y_p)
	{
		t_x = (x / 50 - (int)x / 50) * p->south.wight;
	}
	if (verti == 2 && x > p->x_p){
		t_x = (y / 50 - (int)y / 50) * p->west.wight;
	}
	if (verti == 2 && x < p->x_p){
		t_x = (y / 50 - (int)y / 50) * p->east.wight;
	}
	while(r < start)
		put_one_pixel(p, i, r++, p->sky);
	while (start < end)
	{
		if (verti == 1  && y <= p->y_p){
			t_y = (j / wall_h) * p->north.hight;
			color = get_color_n(&p->north, t_y, t_x);
		}
		if (verti == 1 && y > p->y_p){
			t_y = (j / wall_h) * p->south.hight;
			color = get_color_s(&p->south, t_y, t_x);
		}
		if (verti == 2 && x > p->x_p){
			t_y = (j / wall_h) * p->west.hight;
			color = get_color_w(&p->west, t_y, t_x);
		}
		if (verti == 2 && x <= p->x_p){
			t_y = (j / wall_h) * p->east.hight;
			color = get_color_e(&p->east, t_y, t_x);
		}
		put_one_pixel(p, i, start, color);
		start++;
		j++;
	}
	while(start < H)
		put_one_pixel(p, i, start++, p->floor);

}

void	put_line(t_mlx *p, int len)
{
	double	ray_x;
	double	ray_y;
	double x;
	double j;
	(void)len;

	j = p->angle + 0.5;
	x = 0;
	while(x < W)
	{
		ray_x = p->x_p;
		ray_y = p->y_p;
		while (1)
		{
			if (p->map[(int)(ray_y - sin(j)) / 50][(int)ray_x / 50] == '1')
			{
				draw_wall(ray_x, ray_y, x, p,j, 1);
				break;
			}
			if (p->map[(int)ray_y / 50][(int)(ray_x + cos(j)) / 50] == '1')
			{
				draw_wall(ray_x, ray_y, x, p,j, 2);
				break;
			}
			else
			{
				ray_x += cos(j);
				ray_y -= sin(j);
			}
		}
		x++;
		j -= 0.0008;
	}
}
void	put_player(t_mlx *p)
{
	put_one_pixel(p,  p->x_p, p->y_p, 16710680);
	put_one_pixel(p,  p->x_p, p->y_p+1, 16710680);
	put_one_pixel(p,  p->x_p, p->y_p-1, 16710680);
	put_one_pixel(p,  p->x_p+1, p->y_p, 16710680);
	put_one_pixel(p,  p->x_p+1, p->y_p+1, 16710680);
	put_one_pixel(p,  p->x_p+1, p->y_p-1, 16710680);
	put_one_pixel(p,  p->x_p-1, p->y_p, 16710680);
	put_one_pixel(p,  p->x_p-1, p->y_p+1, 16710680);
	put_one_pixel(p,  p->x_p-1, p->y_p-1, 16710680);
}