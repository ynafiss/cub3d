/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:19:49 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/21 14:05:35 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define WIDTH 2000

void	put_one_pixel(t_mlx *var,int x, int y, int color)
{
	var->draw_image[y * WIDTH + x] = color;
}

void	put_all_pixel(t_mlx *var,int x, int color)
{
	while(x < WIDTH * WIDTH)
	{
		var->draw_image[x] = color;
		x++;
	}
}

void	put_line(t_mlx *p, int len)
{
	int i;
	double j;
	(void)len;
	double r_x;
	double r_y;
	
	
	i = 1;
	j = 0;
	while(j <= 0.4)
	{
		i  = 1;
		while (1)
		{
			r_x = p->y_p - sin(p->angle + j) * i;
			r_y = p->x_p + cos(p->angle + j) * i; 
			if(p->y_p > r_x && r_y > p->x_p && p->map[(int)r_y / 20][(((int)r_x / 20) + 1)] == '1' && p->map[(int)(r_y / 20)-1][(((int)r_x / 20))] == '1')
				break;
				
			if(p->map[(int)((p->y_p - sin(p->angle + j + 0.0080) * i) / 20)][(int)((p->x_p + cos(p->angle + 0.0080 + j) * i) / 20)] == '1' && p->map[(int)((p->y_p - sin(p->angle + j - 0.0080) * i) / 20)][(int)((p->x_p + cos(p->angle - 0.0080 + j) * i) / 20)] == '1')
				break;			
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)((p->x_p + cos(p->angle + j) * i) / 20)] == '1')
				break;
			put_one_pixel(p,  p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i , 16711680);
			i++;
		}
		j += 0.0008;
	}
	j = 0;
	while(j >= -0.4)
	{
		i  = 1;
		while (1)
		{
			if(p->map[(int)((p->y_p - sin(p->angle + j + 0.0080) * i) / 20)][(int)((p->x_p + cos(p->angle + 0.0080 + j) * i) / 20)] == '1' && p->map[(int)((p->y_p - sin(p->angle + j - 0.0080) * i) / 20)][(int)((p->x_p + cos(p->angle - 0.0080 + j) * i) / 20)] == '1')
				break;	
			if(p->map[(int)((p->y_p - sin(p->angle + j) * i) / 20)][(int)((p->x_p + cos(p->angle + j) * i) / 20)] == '1')
				break;
			put_one_pixel(p,  p->x_p + cos(p->angle + j) * i, p->y_p - sin(p->angle + j) * i , 16711680);
			i++;
		}
		j -= 0.0009;
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

void	player(t_mlx *p, int x, int y)
{
	while (p->map[x])
	{
		y = 0;
		while (p->map[x][y])
		{
			 if (p->map[x][y] == 'N' || p->map[x][y] == 'S' || p->map[x][y] == 'W' || p->map[x][y] == 'E')
			{
				p->x_p = y * 20 + 10;
				p->y_p = x * 20 + 10;
				put_one_pixel(p,  p->x_p, p->y_p, 65280);
				put_line(p, 25);
			}
			y++;
		}
		x++;
	}
}

void	ft_fill_map(t_mlx *p, int x, int y)
{
	while (p->map[x])
	{
		y = 0;
		while (p->map[x][y])
		{
			if (p->map[x][y] == '1')
					draw_rect(p, y, x, 0, 0, 65535);
			y++;
		}
		x++;
	}
}

void	ft_move_dir(char **map, t_mlx *p, int x, int y)
{
	(void)y;
	(void)x;
	
	put_all_pixel(p,0, 0);
	ft_fill_map(p, 0, 0);
	if(p->dir == 'u')
	{
		if(map[(int)((p->y_p - sin(p->angle)) / 20)][(int)((p->x_p + cos(p->angle)) / 20)] != '1')
		{
			p->x_p  = p->x_p + cos(p->angle);
			p->y_p  = p->y_p - sin(p->angle);
		}
		put_one_pixel(p,  p->x_p, p->y_p, 65280);
		put_line(p, 25);
	}
	else if(p->dir == 'd')
	{
		if(map[(int)((p->y_p + sin(p->angle)) / 20)][(int)((p->x_p - cos(p->angle)) / 20)] != '1' )
		{
			p->x_p  = p->x_p - cos(p->angle);
			p->y_p  = p->y_p + sin(p->angle);
		}
		put_one_pixel(p,  p->x_p, p->y_p, 65280);
		put_line(p, 25);
	}
	else if(p->dir == 'l')
	{
		if(map[(int)((p->y_p - sin(p->angle + M_PI/2)) / 20)][(int)((p->x_p + cos(p->angle + M_PI/2)) / 20)] != '1' )
		{
			p->x_p  = p->x_p + cos(p->angle + M_PI/2);
			p->y_p  = p->y_p - sin(p->angle + M_PI/2);
		}
		put_one_pixel(p,  p->x_p, p->y_p, 65280);
		put_line(p, 25);
	}
	else if(p->dir == 'r')
	{
		if(map[(int)((p->y_p - sin(p->angle - M_PI/2)) / 20)][(int)((p->x_p + cos(p->angle - M_PI/2)) / 20)] != '1')
		{
			p->x_p  = p->x_p + cos(p->angle - M_PI/2);
			p->y_p  = p->y_p - sin(p->angle - M_PI/2);
		}
		put_one_pixel(p,  p->x_p, p->y_p, 65280);
		put_line(p, 25);
	}
}

int	move_key(int m, t_mlx *p)
{ 
	if (m == 53)
		exit(0);
	if (m == 0 )
		p->dir = 'l';
	else if (m == 2 )
		p->dir = 'r';
	else if (m == 13)
		p->dir = 'u';
	else if (m == 1)
		p->dir = 'd';
 	else if(m == 124)
	{
		put_all_pixel(p,0, 0);
		ft_fill_map(p, 0, 0);
		p->angle -= 0.1;
		if (p->angle <= 0)
			p->angle = 2 * M_PI;
		put_one_pixel(p,  p->x_p, p->y_p, 65280);
		put_line(p, 25);
	}
	else if(m == 123)
	{
		put_all_pixel(p,0, 0);
		ft_fill_map(p, 0, 0);
		if (p->angle >= 2 * M_PI)
			p->angle = 0;
		p->angle += 0.1;
		put_one_pixel(p,  p->x_p, p->y_p, 65280);
		put_line(p, 25);
	}
	if (m == 0 ||  m == 2 || m == 13 || m == 1)
		ft_move_dir(p->map, p, 0, 0);
		mlx_put_image_to_window(p->mlx_ptr, p->mlx_win, p->img_ptr, 0, 0);
		
	return (0);
}

int	ft_close(t_mlx *p)
{
	mlx_destroy_window(p->mlx_ptr, p->mlx_win);
	exit(0);
}

void  exc(t_arg *arg , char **map)
{
	(void)arg;
	(void)map;
	int x;
	int y;

	x = 0;
	y = 0;
	t_mlx p;
	p.map = map;
	p.angle = 0;


	p.mlx_ptr = mlx_init();
	p.mlx_win = mlx_new_window(p.mlx_ptr, 2000, 2000, "cub3D");
	p.img_ptr = mlx_new_image(p.mlx_ptr, 2000, 2000);
	p.draw_image = (unsigned int *)mlx_get_data_addr(p.img_ptr, &p.bits_per_pixel, &p.line_length, &p.endian);
	player(&p, 0, 0);
	ft_fill_map(&p, 0, 0);
	mlx_put_image_to_window(p.mlx_ptr, p.mlx_win, p.img_ptr, 0, 0);
	mlx_hook(p.mlx_win, 2, 0, move_key, &p);
	mlx_hook(p.mlx_win, 17, 0, ft_close, &p);
	mlx_loop(p.mlx_ptr);
}
