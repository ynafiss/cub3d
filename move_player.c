/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:29:13 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/25 15:50:25 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_move_dir2(char **map, t_mlx *p)
{
	if (p->left == 1)
	{
		if (map[(int)((p->y_p) / 50)][(int)((p->x_p + cos(p->angle + M_PI / 2)
					* 20) / 50)] != '1')
			p->x_p = p->x_p + cos(p->angle + M_PI / 2) * 4;
		if (map[(int)((p->y_p - sin(p->angle + M_PI / 2) * 20)
				/ 50)][(int)(p->x_p / 50)] != '1')
			p->y_p = p->y_p - sin(p->angle + M_PI / 2) * 4;
		put_line(p);
	}
	else if (p->right == 1)
	{
		if (map[(int)(p->y_p / 50)][(int)((p->x_p + cos(p->angle - M_PI / 2)
					* 20) / 50)] != '1')
			p->x_p = p->x_p + cos(p->angle - M_PI / 2) * 4;
		if (map[(int)((p->y_p - sin(p->angle - M_PI / 2) * 20)
				/ 50)][(int)(p->x_p / 50)] != '1')
			p->y_p = p->y_p - sin(p->angle - M_PI / 2) * 4;
		put_line(p);
	}
}

void	ft_move_dir(char **map, t_mlx *p)
{
	if (p->up == 1)
	{
		if (map[(int)((p->y_p) / 50)][(int)((p->x_p + cos(p->angle) * 20)
				/ 50)] != '1')
			p->x_p = p->x_p + cos(p->angle) * 4;
		if (map[(int)((p->y_p - sin(p->angle) * 20) / 50)][(int)((p->x_p)
				/ 50)] != '1')
			p->y_p = p->y_p - sin(p->angle) * 4;
		put_line(p);
	}
	else if (p->down == 1)
	{
		if (map[(int)(p->y_p / 50)][(int)((p->x_p - cos(p->angle) * 20)
				/ 50)] != '1')
			p->x_p = p->x_p - cos(p->angle) * 4;
		if (map[(int)((p->y_p + sin(p->angle) * 20) / 50)][(int)(p->x_p
				/ 50)] != '1')
			p->y_p = p->y_p + sin(p->angle) * 4;
		put_line(p);
	}
	ft_move_dir2(map, p);
}

int	move_player(t_mlx *p)
{
	if (p->rotate_right == 1)
	{
		p->angle -= 0.15;
		if (p->angle <= 0)
			p->angle = 2 * M_PI;
		put_line(p);
	}
	else if (p->rotate_left == 1)
	{
		if (p->angle >= 2 * M_PI)
			p->angle = 0;
		p->angle += 0.15;
		put_line(p);
	}
	if (p->right == 1 || p->left == 1 || p->up == 1 || p->down == 1)
		ft_move_dir(p->map, p);
	mlx_put_image_to_window(p->mlx_ptr, p->mlx_win, p->img_ptr, 0, 0);
	return (0);
}
