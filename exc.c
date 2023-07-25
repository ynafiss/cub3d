/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:45:52 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/25 15:31:41 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "header.h"

void	player(t_mlx *p, int x, int y)
{
	while (p->map[y])
	{
		x = 0;
		while (p->map[y][x])
		{
			if (p->map[y][x] == 'N' || p->map[y][x] == 'S'
				|| p->map[y][x] == 'W' || p->map[y][x] == 'E')
			{
				if (p->map[y][x] == 'W')
					p->angle = 0;
				else if (p->map[y][x] == 'N')
					p->angle = M_PI / 2;
				else if (p->map[y][x] == 'E')
					p->angle = M_PI;
				else if (p->map[y][x] == 'S')
					p->angle = (3 * M_PI) / 2;
				p->x_p = x * 50 + 25;
				p->y_p = y * 50 + 25;
				put_one_pixel(p, p->x_p, p->y_p, 16711680);
				put_line(p);
			}
			x++;
		}
		y++;
	}
}

int	move_key(int m, t_mlx *p)
{
	if (m == 53)
		exit(0);
	if (m == 0)
		p->left = 1;
	else if (m == 2)
		p->right = 1;
	else if (m == 13)
		p->up = 1;
	else if (m == 1)
		p->down = 1;
	else if (m == 123)
		p->rotate_left = 1;
	else if (m == 124)
		p->rotate_right = 1;
	return (0);
}

int	release_key(int m, t_mlx *p)
{
	if (m == 53)
		exit(0);
	if (m == 0)
		p->left = 0;
	else if (m == 2)
		p->right = 0;
	else if (m == 13)
		p->up = 0;
	else if (m == 1)
		p->down = 0;
	else if (m == 123)
		p->rotate_left = 0;
	else if (m == 124)
		p->rotate_right = 0;
	return (0);
}

int	ft_close(t_mlx *p)
{
	mlx_destroy_window(p->mlx_ptr, p->mlx_win);
	exit(0);
}

void	exc(t_arg *arg, char **map)
{
	int		x;
	int		y;
	t_mlx	p;

	x = 0;
	y = 0;
	p.map = map;
	p.angle = 0;
	p.mlx_ptr = mlx_init();
	p.mlx_win = mlx_new_window(p.mlx_ptr, W, H, "cub3D");
	p.img_ptr = mlx_new_image(p.mlx_ptr, W, H);
	p.draw_image = (unsigned int *)mlx_get_data_addr(p.img_ptr,
			&p.bits_per_pixel, &p.line_length, &p.endian);
	textuer_inis(&p, arg);
	player(&p, 0, 0);
	mlx_loop_hook(p.mlx_ptr, &move_player, &p);
	mlx_hook(p.mlx_win, 2, 0, move_key, &p);
	mlx_hook(p.mlx_win, 3, 0, release_key, &p);
	mlx_hook(p.mlx_win, 17, 0, ft_close, &p);
	mlx_loop(p.mlx_ptr);
}
