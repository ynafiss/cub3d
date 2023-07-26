/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textuer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:23:32 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/26 15:49:06 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	textuer2_inis(t_mlx *p, t_arg *arg)
{
	p->west.west = mlx_xpm_file_to_image(p->mlx_ptr, arg->we, &p->west.wight,
			&p->west.hight);
	if (p->west.west == NULL)
		(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->west.west_addr = mlx_get_data_addr(p->west.west,
			&p->west.w_bits_per_pixel, &p->west.w_line_length,
			&p->west.w_endian);
	p->east.east = mlx_xpm_file_to_image(p->mlx_ptr, arg->ea, &p->east.wight,
			&p->east.hight);
	if (p->east.east == NULL)
		(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->east.east_addr = mlx_get_data_addr(p->east.east,
			&p->east.e_bits_per_pixel, &p->east.e_line_length,
			&p->east.e_endian);
	p->sky = arg->c;
	p->floor = arg->f;
	p->left = 0;
	p->right = 0;
	p->up = 0;
	p->down = 0;
	p->rotate_left = 0;
	p->rotate_right = 0;
}

void	textuer_inis(t_mlx *p, t_arg *arg)
{
	p->north.north = mlx_xpm_file_to_image(p->mlx_ptr, arg->no, &p->north.wight,
			&p->north.hight);
	if (p->north.north == NULL)
		(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->north.north_addr = mlx_get_data_addr(p->north.north,
			&p->north.n_bits_per_pixel, &p->north.n_line_length,
			&p->north.n_endian);
	p->south.south = mlx_xpm_file_to_image(p->mlx_ptr, arg->so, &p->south.wight,
			&p->south.hight);
	if (p->south.south == NULL)
		(write(2, "Error\nNo such file or directory", 32), exit(2));
	p->south.south_addr = mlx_get_data_addr(p->south.south,
			&p->south.s_bits_per_pixel, &p->south.s_line_length,
			&p->south.s_endian);
	textuer2_inis(p, arg);
}
