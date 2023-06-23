/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:07:23 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/17 15:39:54 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_sides(char **map)
{
	int	i;
	int	y;

	i = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y] && (map[i][y] == ' ' || map[i][y] == '\t'))
			y++;
		if (map[i][y] != '1')
			ft_error_exit("\033[0;31mERROR :invalid map4!\n");
		if (map[i][ft_strlen(map[i]) - 1] != '1')
			ft_error_exit("\033[0;31mERROR :invalid map5!\n");
		i++;
	}
}

int	*tab_len(char **map, int *len_tab)
{
	int	i;
	int	*tab;

	*(len_tab) = 0;
	while (map[(*len_tab)])
		(*len_tab)++;
	tab = malloc(sizeof(int) * (*len_tab));
	i = 0;
	while (map[i])
	{
		tab[i] = ft_strlen(map[i]);
		i++;
	}
	ft_check_sides(map);
	check_all_sides(map, *len_tab, tab);
	return (tab);
}

void	check_line(int *tab, char **map, int i, int bool)
{
	int	x;

	if (bool == 0)
		x = tab[i - 1];
	else
		x = tab[i + 1];
	while (map[i][x])
	{
		if (map[i][x] == '0')
			ft_error_exit("\033[0;31mERROR :invalid map6!\n");
		x++;
	}
}

void	ft_check_map(char **map)
{
	int	*tab;
	int	i;
	int	len_tab;

	i = 0;
	tab = tab_len(map, &len_tab);
	while (++i < len_tab - 1)
	{
		if (tab[i] > tab[i - 1])
			check_line(tab, map, i, 0);
		if (tab[i] > tab[i + 1])
			check_line(tab, map, i, 1);
	}
	i = -1;
	while (map[len_tab - 1][++i])
	{
		if (map[len_tab - 1][i] == '0')
			ft_error_exit("\033[0;31mERROR :invalid map11!\n");
	}
	i = -1;
	while (map[0][++i])
	{
		if (map[0][i] == '0')
			ft_error_exit("\033[0;31mERROR :invalid map12!\n");
	}
}
