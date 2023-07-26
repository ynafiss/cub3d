/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:03 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/26 21:33:29 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "header.h"

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
	int		x;

	x = 0;
	i = -1;
	all = NULL;
	while (str[++i])
	{
		if (str[i] == ',')
			x++;
	}
	if (x != 2)
		ft_error_exit("\033[0;31mERROR :invalid map 106!\n");
	i = 0;
	tab = my_malloc(sizeof(int) * 3);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i++] == c)
		rgb_help(&i, str, all, tab);
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
	path = ft_strtrim(path, " ");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error_exit("\033[0;31mERROR :invalid map 106!\n");
	return (path);
}

void	help_fill_arg(t_arg *arg, char **data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i <= 5)
	{
		j = 0;
		while (data[i][j] && (data[i][j] == ' ' || data[i][j] == '\t'))
			j++;
		if (data[i][j] == 'N' && data[i][j + 1] == 'O')
			arg->no = ft_get_path(data[i], 'N', 'O');
		else if (data[i][j] == 'S' && data[i][j + 1] == 'O')
			arg->so = ft_get_path(data[i], 'S', 'O');
		else if (data[i][j] == 'W' && data[i][j + 1] == 'E')
			arg->we = ft_get_path(data[i], 'W', 'E');
		else if (data[i][j] == 'E' && data[i][j + 1] == 'A')
			arg->ea = ft_get_path(data[i], 'E', 'A');
		else if (data[i][j] == 'F')
			arg->f = ft_get_rgb(data[i], 'F');
		else if (data[i][j] == 'C')
			arg->c = ft_get_rgb(data[i], 'C');
		else
			ft_error_exit("\033[0;31mERROR :invalid map 106!\n");
	}
}

t_arg	*fill_args(char *str)
{
	t_arg	*arg;
	char	**data;

	data = ft_split(str, '\n');
	arg = my_malloc(sizeof(t_arg));
	help_fill_arg(arg, data);
	return (arg);
}
