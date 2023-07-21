/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 5023/07/12 22:57:02 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/21 21:08:02 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_one_pixel(t_mlx *var,int x, int y, int color)
{
	var->draw_image[y * W + x] = color;
}

// int	get_color(unsigned int *var,int x, int y)
// {
// 	int color;

// 	color = var[y * W + x];
// 	return (color);
// }


void	put_all_pixel(t_mlx *var,int x, int color)
{
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
int    get_color_w(t_mlx *par, t_west *tex, int endy, int pox)
{
    char    *str;
    int        colore;

    if (endy < 0 || endy >= W || pox < 0 || pox >= H)
        return (0);
    str = tex->west_addr + ((int)(endy) *tex->w_line_length)
        + ((int)(pox) *(tex->w_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}

int    get_color_e(t_mlx *par, t_east *tex, int endy, int pox)
{
    char    *str;
    int        colore;

    if (endy < 0 || endy >= W || pox < 0 || pox >= H)
        return (0);
    str = tex->east_addr + ((int)(endy) *tex->e_line_length)
        + ((int)(pox) *(tex->e_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}


int    get_color_n(t_mlx *par, t_north *tex, int endy, int pox)
{
    char    *str;
    int        colore;

    if (endy < 0 || endy >= W || pox < 0 || pox >= H)
        return (0);
    str = tex->north_addr + ((int)(endy) *tex->n_line_length)
        + ((int)(pox) *(tex->n_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}

int    get_color_s(t_mlx *par, t_south *tex, int endy, int pox)
{
    char    *str;
    int        colore;

    if (endy < 0 || endy >= W || pox < 0 || pox >= H)
        return (0);
    str = tex->south_addr + ((int)(endy) *tex->s_line_length)
        + ((int)(pox) *(tex->s_bits_per_pixel / 8));
    colore = *(int *)str;
    return (colore);
}

void draw_wall(double x, double y, double i, t_mlx *p, double angel, int verti)
{	
    double	dest;
	double	wall_h;
	double	start;
	double	end;
	double	t_y;
	double	t_x;
	int		r;
	int color;

	r = 0;
    dest = sqrt(pow((int)(x) - (int)p->x_p, 2) + pow((int)(y) - (int)p->y_p, 2)) / 50;
    if (dest == 0)
        dest = 1;
    wall_h = H / (dest * cos(angel - p->angle));
	start = (H / 2) - (wall_h / 2);
	end = start + wall_h;
	if (verti == 1)
	{
		t_x = (x / 50 - (int)x / 50) * 50;
	}
	if (verti == 2){
		t_x = (y / 50 - (int)y / 50) * 50;
	}
	t_y = 0;
	while(r < start)
		put_one_pixel(p, i, r++, p->sky);
	while (start <= end)
	{
		if (verti == 1  && y <= p->y_p){
			t_y += p->north.hight / wall_h;
			color = get_color_n(p, &p->north, t_y, t_x);
		}
		if (verti == 1 && y > p->y_p){
			t_y += p->south.hight / wall_h;
			color = get_color_s(p, &p->south, t_y, t_x);
		}
		if (verti == 2 && x > p->x_p){
			t_y += p->west.hight / wall_h;
			color = get_color_w(p, &p->west, t_y, t_x);
		}
		if (verti == 2 && x <= p->x_p){
			t_y += p->east.hight / wall_h;
			color = get_color_e(p, &p->east, t_y, t_x);
		}
		put_one_pixel(p, i, start, color);
		start++;
	}
	while(end < H)
		put_one_pixel(p, i, end++, p->floor);

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
				put_one_pixel(p, ray_x, ray_y, 16710680);
				ray_x += cos(j) / 3;
				ray_y -= sin(j) / 3;
			}
		}
		x++;
		j -= 0.0008;
	}
	ft_fill_map(p, 0, 0);
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