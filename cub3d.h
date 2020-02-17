/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:35:29 by pohl              #+#    #+#             */
/*   Updated: 2020/02/17 13:44:26 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAX_OBJ 100

# include "libft/libft.h"

typedef struct		s_object
{
	int				type;
	int				face;
	// Delete next line
	char			cardinal_face;
	double			hit_location;
	double			distance;
}					t_object;

typedef struct		s_obj_list
{
	t_object		obj[MAX_OBJ];
	int				size;
}					t_obj_list;

typedef struct		s_2int
{
	int				x;
	int				y;
}					t_2int;

typedef struct		s_2double
{
	double			x;
	double			y;
}					t_2double;

typedef struct		s_texture
{
	void			*ptr;
	int				*data;
	int				size_line;
	t_2int			size;
}					t_texture;

typedef struct		s_config
{
	t_2int			res;
	char			*n_texture;
	char			*s_texture;
	char			*e_texture;
	char			*w_texture;
	char			*sprite_texture;
	t_texture		wall[5];
	int				f_col;
	int				c_col;
	int				**map;
	t_2int			map_size;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	double			*angles;
	t_2double		player_pos;
	double			player_angle;
	int				mvt_forward;
	int				mvt_sideways;
	int				rot;
	t_object		*objects;
}					t_config;

int			cub3d(t_config *config);
void		ray(t_2double pos, double angle, int **input_map, t_obj_list *list);
int			darken(int	color, double distance);

// TODO: Delete next line
int		testest(t_config config);

#endif
