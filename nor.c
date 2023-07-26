/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:33:05 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/26 21:33:44 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_all_nor(int i, int j, char **map, int *tab)
{
	if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
		ft_error_exit("\033[0;31mERROR :invalid map8!\n");
	if (j > 0 && map[i][j - 1] != '1' && map[i][j - 1] != ' ')
		ft_error_exit("\033[0;31mERROR :invalid map9!\n");
	if (i > 0 && j < tab[i - 1] && map[i - 1][j] != '1' && map[i - 1][j] != ' ')
		ft_error_exit("\033[0;31mERROR :invalid map---!\n");
}

void	check_all_nor2(int *x, int i, int j, char **map)
{
	if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
		|| map[i][j] == 'E')
		(*x)++;
	if (check_character(map[i][j]) == 1)
		ft_error_exit("\033[0;31mERROR :invalid map7!\n");
}

void	rgb_help(int *i, char *str, char **all, int *tab)
{
	while (str[(*i)] && str[(*i)] == ' ')
		(*i)++;
	all = ft_split(&str[(*i)], ',');
	(*i) = -1;
	while (all[++(*i)])
		all[(*i)] = ft_strtrim(all[(*i)], " ");
	if (count(all) != 3)
		ft_error_exit("\033[0;31mERROR :invalid map 144!\n");
	(*i) = -1;
	while (all[++(*i)])
		tab[(*i)] = check_int(all[(*i)]);
}
