/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:01:44 by ynafiss           #+#    #+#             */
/*   Updated: 2023/07/21 20:56:20 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	player(t_mlx *p, int x, int y)
{
	while (p->map[y])
	{
		x = 0;
		while (p->map[y][x])
		{
			 if (p->map[y][x] == 'N' || p->map[y][x] == 'S' || p->map[y][x] == 'W' || p->map[y][x] == 'E')
			{
				p->x_p = x * 50 + 25;
				p->y_p = y * 50 + 25;
				put_one_pixel(p,  p->x_p, p->y_p, 16711680);
				put_line(p, 25);
			}
			x++;
		}
		y++;
	}
}

void	ft_fill_map(t_mlx *p, int x, int y)
{
	int i;
	while (p->map[y])
	{
		i = 0;
		while (i < 20)
		{
				put_one_pixel(p,  x * 20 + i, y * 20,  65535);
				put_one_pixel(p,  x  * 20, y * 20 + i,  65535);
			i++;
		}
		x = 0;
		while (p->map[y][x])
		{
			i = 0;
			while (i < 20)
			{
				put_one_pixel(p,  x * 20 + i, y * 20,  65535);
				put_one_pixel(p,  x  * 20, y * 20 + i,  65535);
				i++;
			}
			if (p->map[y][x] == '1')
					draw_rect(p, x, y, 0, 0, 65535);
			x++;
		}
		y++;
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
		if(map[(int)((p->y_p - sin(p->angle)) / 50)][(int)((p->x_p + cos(p->angle)) / 50)] != '1')
		{
			p->x_p  = p->x_p + cos(p->angle) * 8;
			p->y_p  = p->y_p - sin(p->angle) * 8;
		}
		put_player(p);
		put_line(p, 25);
	}
	else if(p->dir == 'd')
	{
		if(map[(int)((p->y_p + sin(p->angle)) / 50)][(int)((p->x_p - cos(p->angle)) / 50)] != '1' )
		{
			p->x_p  = p->x_p - cos(p->angle) * 8;
			p->y_p  = p->y_p + sin(p->angle) * 8;
		}
	put_player(p);
		put_line(p, 25);
	}
	else if(p->dir == 'l')
	{
		if(map[(int)((p->y_p - sin(p->angle + M_PI/2)) / 50)][(int)((p->x_p + cos(p->angle + M_PI/2)) / 50)] != '1' )
		{
			p->x_p  = p->x_p + cos(p->angle + M_PI/2) * 8;
			p->y_p  = p->y_p - sin(p->angle + M_PI/2) * 8;
		}
	put_player(p);
		put_line(p, 25);
	}
	else if(p->dir == 'r')
	{
		if(map[(int)((p->y_p - sin(p->angle - M_PI/2)) / 50)][(int)((p->x_p + cos(p->angle - M_PI/2)) / 50)] != '1')
		{
			p->x_p  = p->x_p + cos(p->angle - M_PI/2) * 8;
			p->y_p  = p->y_p - sin(p->angle - M_PI/2) * 8;
		}
		put_player(p);
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
			put_player(p);
		put_line(p, 25);
	}
	else if(m == 123)
	{
		put_all_pixel(p,0, 0);
		ft_fill_map(p, 0, 0);
		if (p->angle >= 2 * M_PI)
			p->angle = 0;
		p->angle += 0.1;
put_player(p);
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

void	textuer_inis(t_mlx *p, t_arg *arg)
{
	int	x;
	int	y;
	p->north.north = mlx_xpm_file_to_image (p->mlx_ptr, arg->no, &x, &p->north.hight);
	if (p->north.north == NULL)
			(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->north.north_addr = mlx_get_data_addr(p->north.north, &p->north.n_bits_per_pixel, &p->north.n_line_length, &p->north.n_endian);
	p->south.south = mlx_xpm_file_to_image (p->mlx_ptr, arg->so, &x, &p->south.hight);
	if (p->south.south == NULL)
			(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->south.south_addr = mlx_get_data_addr(p->south.south, &p->south.s_bits_per_pixel, &p->south.s_line_length, &p->south.s_endian);
	p->west.west = mlx_xpm_file_to_image (p->mlx_ptr, arg->we, &x, &p->west.hight);
	if (p->west.west == NULL)
			(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->west.west_addr = mlx_get_data_addr(p->west.west, &p->west.w_bits_per_pixel, &p->west.w_line_length, &p->west.w_endian);
	p->east.east = mlx_xpm_file_to_image (p->mlx_ptr, arg->ea, &x, &p->east.hight);
	if (p->east.east == NULL)
			(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->east.east_addr = mlx_get_data_addr(p->east.east, &p->east.e_bits_per_pixel, &p->east.e_line_length, &p->east.e_endian);
	p->sky = arg->c;
	p->floor = arg->f;
}

void  exc(t_arg *arg , char **map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	t_mlx p;
	p.map = map;
	p.angle = 0;


	p.mlx_ptr = mlx_init();
	p.mlx_win = mlx_new_window(p.mlx_ptr,W, H, "cub3D");
	p.img_ptr = mlx_new_image(p.mlx_ptr, W, H);
	p.draw_image = (unsigned int *)mlx_get_data_addr(p.img_ptr, &p.bits_per_pixel, &p.line_length, &p.endian);
	textuer_inis(&p, arg);
	player(&p, 0, 0);
	ft_fill_map(&p, 0, 0);
	mlx_put_image_to_window(p.mlx_ptr, p.mlx_win, p.img_ptr, 0, 0);
	mlx_hook(p.mlx_win, 2, 0, move_key, &p);
	mlx_hook(p.mlx_win, 17, 0, ft_close, &p);
	mlx_loop(p.mlx_ptr);
}
