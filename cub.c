/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:57:25 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/26 21:14:32 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	helper(int *count, char *tmp, char **data)
{
	if ((*count) > 0 && check_empty(tmp) == 1)
	{
		if ((*count) > 1)
			*data = ft_strjoin(*data, ft_strdup(tmp));
		(*count)--;
	}
	else if ((*count) == 0 && check_empty(tmp) == 0)
		ft_error_exit("\033[0;31mERROR :invalid map2!\n");
}

char	*ft_read_map(char *str, char **data)
{
	int		fd;
	char	*s;
	char	*tmp;
	int		count;

	count = 7;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_error_exit("\033[0;31mERROR :invalid map1!\n");
	tmp = get_next_line(fd);
	helper(&count, tmp, data);
	s = ft_strdup("");
	while (tmp)
	{
		s = ft_strjoin(s, tmp);
		tmp = get_next_line(fd);
		if (tmp == NULL)
		{
			if (count > 0)
				ft_error_exit("\033[0;31mERROR :invalid map1!\n");
			break ;
		}
		helper(&count, tmp, data);
	}
	return (s);
}

int	check_cub(char *str)
{
	char	*s;

	s = ft_strrchr(str, '.');
	if (s == NULL)
		return (0);
	if (ft_memcmp(s, ".cub\0", 5) == 0)
		return (1);
	return (0);
}

int	count(char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	char	*file;
	char	**tmp;
	char	**map;
	char	*data;
	t_arg	*arg;

	if (ac == 2)
	{
		if (check_cub(av[1]) == 0)
			ft_error_exit("\033[0;33mERROR! :extension must be [.cub]");
		data = ft_strdup("");
		file = ft_read_map(av[1], &data);
		tmp = ft_split(file, '\n');
		map = &tmp[6];
		ft_check_map(map);
		arg = fill_args(data);
		exc(arg, map);
	}
}
