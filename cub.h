/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:50:20 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/19 19:44:39 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_arg
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
}			t_arg;

typedef struct need_hook
{
	int		len;
	int		high;
	double		coins;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	**map;
	int		save_a;
	int		save_b;
	int		dir;
	int		moves;
	double 	x_p;
	double 	y_p;
	double 	angle;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned int	*draw_image;
	void			*img_ptr;
}			t_mlx;

char		*get_next_line(int fd);
void		ft_error_exit(char *str);
void		check_all_sides(char **map, int len, int *tab);
void		ft_check_map(char **map);
int			check_empty(char *str);
t_arg		*fill_args(char *str);
void		exc(t_arg *arg, char **map);
#endif