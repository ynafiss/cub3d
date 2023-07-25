/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:50:20 by rchmouk           #+#    #+#             */
/*   Updated: 2023/07/24 23:21:06 by ynafiss          ###   ########.fr       */
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
# include <stdint.h> 
# include <string.h>

# define W 1200
# define H 1000
# define PI 3.14159
# define TOW_PI PI * 2
# define FOV 60 * (PI / 180)
# define RAYS_NUM 100
# define TAILE 50

typedef struct s_arg
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f;
	int				c;
}					t_arg;

typedef struct s_ray
{
	double	angel;
	double	hit_x;
	double	hit_y;
	double	dest;
	int		is_vertial;
	int	x_inter;
	int y_inter;
	double	x_step;
	double y_step;
	double	check_x;
	double	check_y;
	int	is_it_wall;
	double	horez_wall_y ;
	double	horez_wall_x ;
	double	next_horez_wall_y;
	double	next_horez_wall_x;
	int		is_ray_right;
	int		is_ray_left;
	int		is_ray_down;
	int		is_ray_up;
	double	verti_wall_y;
	double	verti_wall_x;
	double	next_verti_wall_y;
	double	next_verti_wall_x;
}t_rays;

typedef struct s_north
{
	void			*north;
	char			*north_addr;
	int				n_bits_per_pixel;
	int				n_line_length;
	int				n_endian;
	int				hight;
	int				wight;
}t_north;

typedef struct s_west
{
	void			*west;
	int				w_bits_per_pixel;
	int				w_line_length;
	int				w_endian;	
	char			*west_addr;
	int				hight;
	int				wight;
}t_west;

typedef struct s_east
{	
	void			*east;
	int				e_bits_per_pixel;
	int				e_line_length;
	int				e_endian;
	char			*east_addr;
	int				hight;
	int				wight;
}t_east;

typedef struct s_south
{
	void			*south;	
	int				s_bits_per_pixel;
	int				s_line_length;
	int				s_endian;
	char			*south_addr;
	int				hight;
	int				wight;
}t_south;
// 	if(p->up == 1)
// 	{
// 			if (map[(int)((p->y_p ) / 50)][(int)((p->x_p + cos(p->angle) * 12) / 50)] != '1')
// 				p->x_p  = p->x_p + cos(p->angle) * 4;
// 			if (map[(int)((p->y_p - sin(p->angle) * 12) / 50)][(int)((p->x_p) / 50)] != '1')
// 				p->y_p  = p->y_p - sin(p->angle) * 4;
// 		put_line(p, 25);
// 	}
// 	else if(p->down == 1)
// 	{
// 			if (map[(int)(p->y_p / 50)][(int)((p->x_p - cos(p->angle) * 12) / 50)] != '1')
// 				p->x_p  = p->x_p - cos(p->angle) * 4;
// 			if (map[(int)((p->y_p + sin(p->angle) * 12) / 50)][(int)(p->x_p / 50)] != '1' )
// 				p->y_p  = p->y_p + sin(p->angle) * 4;
// 		put_line(p, 25);
// 	}
// 	else if(p->left == 1)
// 	{
// 			if (map[(int)((p->y_p) / 50)][(int)((p->x_p + cos(p->angle + M_PI/2) * 12) / 50)] != '1' )
// 				p->x_p  = p->x_p + cos(p->angle + M_PI/2) * 4;
// 			if (map[(int)((p->y_p - sin(p->angle + M_PI/2) * 12) / 50)][(int)(p->x_p / 50)] != '1')
// 			p->y_p  = p->y_p - sin(p->angle + M_PI/2) * 4;
// 		put_line(p, 25);
// 	}
// 	else if(p->right == 1)
// 	{
// 			if (map[(int)(p->y_p / 50)][(int)((p->x_p + cos(p->angle - M_PI/2) * 12) / 50)] != '1')
// 				p->x_p  = p->x_p + cos(p->angle - M_PI/2) * 4;
// 			if (map[(int)((p->y_p - sin(p->angle - M_PI/2) * 12) / 50)][(int)(p->x_p / 50)] != '1')
// 			p->y_p  = p->y_p - sin(p->angle - M_PI/2) * 4;
// 		put_line(p, 25);
// 	}
// }

typedef struct need_hook
{
	int				len;
	int				sky;
	int				floor;
	int				vertical;
	int				right;
	int				left;
	int				up;
	int				down;
	int				rotate_right;
	int				rotate_left;
	int				high;
	double			old_x;
	double			old_y;
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
	double			x_ray;
	double			y_ray;
	t_west			west;
	t_east			east;
	t_north			north;
	t_south			south;
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
void				put_line(t_mlx *p);
void				draw_sky_floor(t_mlx *p, double start, int i, double end);
void				put_player(t_mlx *p);
void				ft_fill_map(t_mlx *p, int x, int y);
int    get_color_w(t_west *tex, int y, int x);
int    get_color_e(t_east *tex, int y, int x);
int    get_color_n(t_north *tex, int y, int x);
int    get_color_s(t_south *tex, int y, int x);

#endif