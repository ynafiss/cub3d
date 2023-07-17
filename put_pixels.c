/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:57:02 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/16 04:23:21 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_one_pixel(t_mlx *var,int x, int y, int color)
{
	var->draw_image[y * W + x] = color;
}

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
    while(height < 20)
    {
        width = 0;
        while(width < 20)
        {
            put_one_pixel(var, x * 20 + width, y * 20 + height, color);
            width++;
        }
        height++;
    }
}

void	draw_wall(double x, double y, int i, t_mlx *p, double j, int color, int h_v)
{
	double	start;
	double	end;
	double	wall;
	double dest;

	dest = sqrt(pow((int)x - (int)p->x_p, 2) + pow((int)y - (int)p->y_p, 2)) / 20;
	wall = H / (dest * cos(j));
	start = (1000 - wall) / 2;
	end = start + wall;
	if (h_v == 1 && y < p->y_p)
		color = 16711680;
	if (h_v == 1 && y > p->y_p)
		color = 16711660;
	if (h_v == 0 && x > p->x_p)
		color = 16411660;
	if (h_v == 0 && x < p->x_p)
		color = 16511660;
	if (end > H)
		end = H;
	while (start <= end)
	{
		put_one_pixel(p, i, start, color);
		start++;
	}
}

void	put_line(t_mlx *p, int len)
{
	int i;
	double	ray_x;
	double	ray_y;
	int		vertical;
	int x = 0;
	double j;
	(void)len;
	
	i = 1;
	j = 0;
	x = W / 2;
	while(j <= 0.4 && x > 0)
	{
		i  = 1;
		while (1)
		{
			ray_x = (p->x_p + cos(p->angle + j) * i);
			ray_y = (p->y_p - sin(p->angle + j) * i);
			p->old_x = (p->x_p + cos(p->angle + j) * (i - 1));
			p->old_y = (p->y_p - sin(p->angle + j) * (i - 1));
			if(p->map[(int)(ray_y / 20)][(int)(ray_x / 20)] == '1'){
				if (p->map[(int)(ray_y / 20)][(int)((p->old_x)/ 20)] == '1')
					vertical = 1;
				else if (p->map[(int)(p->old_y / 20)][(int)((ray_x)/ 20)] == '1')
					vertical = 0;
				draw_wall(p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i, x, p, j, 26711680, vertical);
				break;
			}
				put_one_pixel(p,  p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i , 16711680);
			if(p->map[(int)(ray_y / 20)][(int)((ray_x + 1)/ 20)] == '1' && p->map[(int)((ray_y - 1 )/ 20)][(int)(ray_x / 20)] == '1'){
				if (p->map[(int)(ray_y / 20)][(int)((p->old_x + 1)/ 20)] == '1')
					vertical = 1;
				else if (p->map[(int)(p->old_y / 20)][(int)((ray_x + 1)/ 20)] == '1')
					vertical = 0;
				draw_wall(p->x_p + cos(p->angle + j) * i, ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, vertical);
				break;
			}
			if(p->map[(int)(ray_y / 20)][(int)((ray_x)/ 20)] == '1' && p->map[(int)((ray_y - 1 )/ 20)][(int)(ray_x / 20)] == '1'){
				if (p->map[(int)(ray_y / 20)][(int)((p->old_x)/ 20)] == '1')
					vertical = 1;
				else if (p->map[(int)((p->old_y - 1) / 20)][(int)((ray_x)/ 20)] == '1')
					vertical = 0;
				draw_wall(p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i, x, p, j, 26711680, vertical);
				break;
			}
			i++;
		}
		x--;
		j += 0.0008;
	}
	j = 0;
	x = W / 2;
	while(j >= -0.4 && x < W)
	{
		i  = 1;
		while (1)
		{
			ray_x = (p->x_p + cos(p->angle + j) * i);
			ray_y = (p->y_p - sin(p->angle + j) * i);
			p->old_x = (p->x_p + cos(p->angle + j) * (i - 1));
			p->old_y = (p->y_p - sin(p->angle + j) * (i - 1));
			if(p->map[(int)(ray_y / 20)][(int)(ray_x / 20)] == '1'){
				if (p->map[(int)(ray_y / 20)][(int)((p->old_x)/ 20)] == '1')
					vertical = 1;
				else if (p->map[(int)(p->old_y / 20)][(int)((ray_x)/ 20)] == '1')
					vertical = 0;
				draw_wall(p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i, x, p, j, 26711680, vertical);
				break;
			}
				put_one_pixel(p,  p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i , 16711680);
			if(p->map[(int)(ray_y / 20)][(int)((ray_x + 1)/ 20)] == '1' && p->map[(int)((ray_y - 1 )/ 20)][(int)(ray_x / 20)] == '1'){
				if (p->map[(int)(ray_y / 20)][(int)((p->old_x + 1)/ 20)] == '1')
					vertical = 1;
				else if (p->map[(int)(p->old_y / 20)][(int)((ray_x + 1)/ 20)] == '1')
					vertical = 0;
				draw_wall(p->x_p + cos(p->angle + j) * i, ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, vertical);
				break;
			}
			if(p->map[(int)(ray_y / 20)][(int)((ray_x)/ 20)] == '1' && p->map[(int)((ray_y - 1 )/ 20)][(int)(ray_x / 20)] == '1'){
				if (p->map[(int)(ray_y / 20)][(int)((p->old_x)/ 20)] == '1')
					vertical = 1;
				else if (p->map[(int)((p->old_y - 1) / 20)][(int)((ray_x)/ 20)] == '1')
					vertical = 0;
				draw_wall(p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i, x, p, j, 26711680, vertical);
				break;
			}
			i++;
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