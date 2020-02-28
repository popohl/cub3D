/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:35:29 by pohl              #+#    #+#             */
/*   Updated: 2020/02/28 20:47:13 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAX_OBJ 100
# define MAX_SCREEN_W 2560
# define MAX_SCREEN_H 1440

// Delete next line
# include "debug.h"

# include "libft/libft.h"

typedef struct			s_object
{
	int					type;
	int					face;
	double				hit_location;
	double				distance;
}						t_object;

typedef struct			s_obj_list
{
	t_object			obj[MAX_OBJ];
	int					size;
}						t_obj_list;

typedef struct			s_2int
{
	int					x;
	int					y;
}						t_2int;

typedef struct			s_2double
{
	double				x;
	double				y;
}						t_2double;

typedef struct			s_texture
{
	void				*ptr;
	int					*data;
	int					sl;
	t_2int				size;
}						t_texture;

typedef struct			s_config
{
	t_2int				res;
	t_texture			wall[5];
	int					f_col;
	int					c_col;
	char				**map;
	t_2int				map_size;
	void				*mlx_ptr;
	void				*win_ptr;
	t_texture			img;
	double				*angles;
	t_2double			pl_pos;
	double				pl_angle;
	int					mvt_forward;
	int					mvt_side;
	int					rot;
	t_obj_list			*list;
}						t_config;

typedef union			u_col
{
	int					i;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}					c;
}						t_col;

int						cub3d(t_config *config);
void					ray(t_2double pos, double angle, char **map,
								t_obj_list *l);
int						darken(int	color, double distance);
int						read_res(t_config *config, char *line);
int						read_col(t_config *config, char *line);
int						read_tex(t_config *config, char *line);
int						read_map(t_config *config, char *line);
int						check_map(t_config *config);
int						print_map(char **map, t_2int map_size);
int						count_digits(char *str, int *width);
void					color_error(char *line);
void					tex_error(char *line);

#endif
