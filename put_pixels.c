/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:57:02 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/14 19:47:01 by ynafiss          ###   ########.fr       */
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
(void)h_v;
	dest = sqrt(pow((int)x - (int)p->x_p, 2) + pow((int)y - (int)p->y_p, 2)) / 20;
	wall = H / (dest * cos(j));
	start = (1000 - wall) / 2;
	end = start + wall;
	while (start <= end)
	{
		put_one_pixel(p, i, start, color);
		start++;
	}
	printf("%d\n", c);
}

void	put_line(t_mlx *p, int len)
{
	int i;
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
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)((p->x_p + cos(p->angle + j) * i) / 20)] == '1'){
				draw_wall((p->x_p + cos(p->angle + j) * i), ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, 1);
				break;
			}
				put_one_pixel(p,  p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i , 16711680);
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)(((p->x_p + cos(p->angle + j) * i) + 1)/ 20)] == '1' && p->map[(int)(((p->y_p - sin(p->angle + j) * i) - 1 )/ 20)][(int)((p->x_p + cos(p->angle + j) * i)/ 20)] == '1'){
				draw_wall((((p->x_p + cos(p->angle + j) * i) + 1)), ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, 1);
				break;
			}
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)(((p->x_p + cos(p->angle + j) * i) - 1)/ 20)] == '1' && p->map[(int)(((p->y_p - sin(p->angle + j) * i) - 1 )/ 20)][(int)((p->x_p + cos(p->angle + j) * i)/ 20)] == '1'){
				draw_wall((((p->x_p + cos(p->angle + j) * i))), ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, 2);
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
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)((p->x_p + cos(p->angle + j) * i) / 20)] == '1'){
				draw_wall(((p->x_p + cos(p->angle + j) * i)), ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, 1);
				break;
			}
			put_one_pixel(p,  p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i , 26711680);
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)(((p->x_p + cos(p->angle + j) * i) + 1)/ 20)] == '1' && p->map[(int)(((p->y_p - sin(p->angle + j) * i) - 1 )/ 20)][(int)((p->x_p + cos(p->angle + j) * i)/ 20)] == '1'){
				draw_wall((((p->x_p + cos(p->angle + j) * i) + 1)), ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, 1);
				break;
			}
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)(((p->x_p + cos(p->angle + j) * i) - 1)/ 20)] == '1' && p->map[(int)(((p->y_p - sin(p->angle + j) * i) - 1 )/ 20)][(int)((p->x_p + cos(p->angle + j) * i)/ 20)] == '1'){
				draw_wall((((p->x_p + cos(p->angle + j) * i) - 1)), ((p->y_p - sin(p->angle + j) * i)), x, p, j, 26711680, 2);
				break;
			}
			i++;
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