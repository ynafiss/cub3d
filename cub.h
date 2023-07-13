/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:50:20 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/13 15:00:32 by rchmouk          ###   ########.fr       */
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

# define W 2000
# define H 2000

typedef struct s_arg
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f;
	int				c;
}					t_arg;

typedef struct need_hook
{
	int				len;
	char			dir;
	int				high;
	void			*mlx_ptr;
	void			*mlx_win;
	void			*mlx_img;
	char			**map;
	double			x_p;
	double			y_p;
	double			angle;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned int	*draw_image;
	void			*img_ptr;
}					t_mlx;

char				*get_next_line(int fd);
void				ft_error_exit(char *str);
void				check_all_sides(char **map, int len, int *tab);
void				ft_check_map(char **map);
int					check_empty(char *str);
t_arg				*fill_args(char *str);
void				exc(t_arg *arg, char **map);
void				put_one_pixel(t_mlx *var, int x, int y, int color);
void				put_all_pixel(t_mlx *var, int x, int color);
void				draw_rect(t_mlx *var, int x, int y, int height, int width,
						int color);
void				put_line(t_mlx *p, int len);
void				put_player(t_mlx *p);

#endif