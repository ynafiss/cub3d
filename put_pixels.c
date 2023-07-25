/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 5023/07/12 22:57:02 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/24 23:20:49 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	get_x_text(t_mlx *p, int verti)
{
	double	t_x;

	if (verti == 1 && p->y_ray <= p->y_p)
	{
		t_x = (p->x_ray / 50 - (int)p->x_ray / 50) * p->north.wight;
	}
	if (verti == 1 && p->y_ray > p->y_p)
	{
		t_x = (p->x_ray / 50 - (int)p->x_ray / 50) * p->south.wight;
	}
	if (verti == 0 && p->x_ray > p->x_p)
	{
		t_x = (p->y_ray / 50 - (int)p->y_ray / 50) * p->west.wight;
	}
	if (verti == 0 && p->x_ray < p->x_p)
	{
		t_x = (p->y_ray / 50 - (int)p->y_ray / 50) * p->east.wight;
	}
	return (t_x);
}

int	get_color(t_mlx *p, double t_x, int j, double wall_h)
{
	double	t_y;
	int		color;

	if (p->vertical == 1 && p->y_ray <= p->y_p)
	{
		t_y = (j / wall_h) * p->north.hight;
		color = get_color_n(&p->north, t_y, t_x);
	}
	if (p->vertical == 1 && p->y_ray > p->y_p)
	{
		t_y = (j / wall_h) * p->south.hight;
		color = get_color_s(&p->south, t_y, t_x);
	}
	if (p->vertical == 0 && p->x_ray > p->x_p)
	{
		t_y = (j / wall_h) * p->west.hight;
		color = get_color_w(&p->west, t_y, t_x);
	}
	if (p->vertical == 0 && p->x_ray <= p->x_p)
	{
		t_y = (j / wall_h) * p->east.hight;
		color = get_color_e(&p->east, t_y, t_x);
	}
	return (color);
}

void	draw_wall(double i, t_mlx *p, double angel)
{	
	double	wall_h;
	double	start;
	double	end;
	double	t_x;
	int		j;

	wall_h = (50 / (sqrt(pow((int)(p->x_ray) - (int)p->x_p, 2) + \
	pow((int)(p->y_ray) - \
	(int)p->y_p, 2)) * cos(angel - p->angle))) * ((W / 2) / tan(FOV / 2));
	j = 0;
	start = (H / 2) - (wall_h / 2);
	if (wall_h >= H)
	{
		while (start < 0)
			start++;
		j = (wall_h - H) / 2;
	}
	end = start + wall_h;
	if (end > H)
		end = H;
	t_x = get_x_text(p, p->vertical);
	draw_sky_floor(p, start, i, end);
	while (start < end)
		put_one_pixel(p, i, start++, get_color(p, t_x, j++, wall_h));
}

int	check_walls(t_mlx *p, double j, int x)
{
	if (p->map[(int)(p->y_ray - sin(j)) / 50][(int)p->x_ray / 50] == '1')
	{
		p->vertical = 1;
		draw_wall(x, p, j);
		return (1);
	}
	if (p->map[(int)p->y_ray / 50][(int)(p->x_ray + cos(j)) / 50] == '1')
	{
		p->vertical = 0;
		draw_wall(x, p, j);
		return (1);
	}
	return (0);
}

void	put_line(t_mlx *p)
{
	double	x;
	double	j;

	j = p->angle + 0.5;
	x = 0;
	while (x < W)
	{
		p->x_ray = p->x_p;
		p->y_ray = p->y_p;
		while (1)
		{
			if (check_walls(p, j, x))
				break ;
			p->x_ray += cos(j);
			p->y_ray -= sin(j);
		}
		x++;
		j -= 0.0008;
	}
}
