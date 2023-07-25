/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:31:54 by ynafiss           #+#    #+#             */
/*   Updated: 2023/07/24 23:23:28 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_one_pixel(t_mlx *var, int x, int y, int color)
{
	if (x < 0 && x > W && y < 0 && y > H)
	{
		printf("x: %d   y: %d\n", x, y);
		return ;
	}
	var->draw_image[y * W + x] = color;
}

void	put_all_pixel(t_mlx *var, int x, int color)
{
	if (x < 0 && x > W)
		return ;
	while (x < W * H)
	{
		var->draw_image[x] = color;
		x++;
	}
}

void	draw_sky_floor(t_mlx *p, double start, int i, double end)
{
	int	r;

	r = 0;
	while (r < start)
		put_one_pixel(p, i, r++, p->sky);
	while (end < H)
		put_one_pixel(p, i, end++, p->floor);
}
