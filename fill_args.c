/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:03 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/17 20:18:39 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_int(char *str)
{
	int	len;
	int	i;
	int	x;

	i = 0;
	len = ft_strlen(str);
	if (len > 3)
		ft_error_exit("\033[0;31mERROR :invalid map 101!\n");
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			ft_error_exit("\033[0;31mERROR :invalid map 102!\n");
		i++;
	}
	x = ft_atoi(str);
	if (x > 255)
		ft_error_exit("\033[0;31mERROR :invalid map 102!\n");
	return (x);
}

int	ft_get_rgb(char *str, char c)
{
	int		i;
	int		*tab;
	char	**all;

	i = 0;
	tab = malloc(sizeof(int) * 3);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == c)
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		all = ft_split(&str[i], ',');
		i = -1;
		while (all[++i])
		{
			if (i > 2)
				ft_error_exit("\033[0;31mERROR :invalid map 103!\n");
			tab[i] = check_int(all[i]);
		}
	}
	else
		ft_error_exit("\033[0;31mERROR :invalid map 104!\n");
	return ((tab[0] << 16) + (tab[1] << 8) + tab[2]);
}

char	*ft_get_path(char *str, char a, char b)
{
	int		i;
	int		fd;
	char	*path;

	path = NULL;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == a && str[i + 1] == b)
	{
		i = i + 2;
		while (str[i] && str[i] == ' ')
			i++;
		path = ft_substr(str, i, ft_strlen(str));
	}
	else
		ft_error_exit("\033[0;31mERROR :invalid map 105!\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error_exit("\033[0;31mERROR :invalid map 106!\n");
	return (path);
}

t_arg	*fill_args(char *str)
{
	t_arg	*arg;
	char	**data;

	data = ft_split(str, '\n');
	arg = malloc(sizeof(t_arg));
	arg->no = ft_get_path(data[0], 'N', 'O');
	arg->so = ft_get_path(data[1], 'S', 'O');
	arg->we = ft_get_path(data[2], 'W', 'E');
	arg->ea = ft_get_path(data[3], 'E', 'A');
	arg->f = ft_get_rgb(data[4], 'F');
	arg->c = ft_get_rgb(data[5], 'C');
	return (arg);
}
