/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:09:51 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/17 21:50:13 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_error_exit(char *str)
{
	printf("%s", str);
	exit(1);
}

int	check_character(char c)
{
	static int	x;

	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (x == 1)
			ft_error_exit("\033[0;31mERROR :invalid map6.5!\n");
		else
		{
			x = 1;
			return (0);
		}
	}
	if (c == '1' || c == '0' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

void	check_all_sides(char **map, int len, int *tab)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (check_character(map[i][j]) == 1)
				ft_error_exit("\033[0;31mERROR :invalid map7!\n");
			if (map[i][j] == ' ' || map[i][j] == '\t')
			{
				if (map[i][j + 1] == '0')
					ft_error_exit("\033[0;31mERROR :invalid map8!\n");
				if (j > 0 && map[i][j - 1] == '0')
					ft_error_exit("\033[0;31mERROR :invalid map9!\n");
				if (i > 0 && i <= tab[i - 1] && map[i - 1][j] == '0')
					ft_error_exit("\033[0;31mERROR :invalid map!\n");
				if (i < len - 1 && i <= tab[i + 1] && map[i + 1][j] == '0')
					ft_error_exit("\033[0;31mERROR :invalid map10!\n");
			}
		}
		i++;
	}
}
