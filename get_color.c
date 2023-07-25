/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:30:56 by ynafiss           #+#    #+#             */
/*   Updated: 2023/07/24 23:27:37 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_color_w(t_west *tex, int y, int x)
{
	char	*str;
	int		colore;

	if (y < 0 || y > H || x < 0 || x > W)
		return (0);
	str = tex->west_addr + ((int)(y) *tex->w_line_length)
		+ ((int)(x) *(tex->w_bits_per_pixel / 8));
	colore = *(int *)str;
	return (colore);
}

int	get_color_e(t_east *tex, int y, int x)
{
	char	*str;
	int		colore;

	if (y < 0 || y > H || x < 0 || x > W)
		return (0);
	str = tex->east_addr + ((int)(y) *tex->e_line_length)
		+ ((int)(x) *(tex->e_bits_per_pixel / 8));
	colore = *(int *)str;
	return (colore);
}

int	get_color_n(t_north *tex, int y, int x)
{
	char	*str;
	int		colore;

	if (y < 0 || y > H || x < 0 || x > W)
		return (0);
	str = tex->north_addr + ((int)(y) *tex->n_line_length)
		+ ((int)(x) *(tex->n_bits_per_pixel / 8));
	colore = *(int *)str;
	return (colore);
}

int	get_color_s(t_south *tex, int y, int x)
{
	char	*str;
	int		colore;

	if (x < 0 || x >= W || y < 0 || y >= H)
		return (0);
	str = tex->south_addr + ((int)(y) *tex->s_line_length)
		+ ((int)(x) *(tex->s_bits_per_pixel / 8));
	color = *(int *)str;
	return (colore);
}
