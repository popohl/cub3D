/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:35:29 by pohl              #+#    #+#             */
/*   Updated: 2020/02/08 21:30:16 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

typedef void*		ptr;

typedef struct		s_config
{
	int				x_res;
	int				y_res;
	char			*n_texture;
	char			*s_texture;
	char			*e_texture;
	char			*w_texture;
	char			*sprite_texture;
	int				f_col;
	int				c_col;
	int				**map;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	double			*angles;
	double			player_posx;
	double			player_posy;
	double			player_angle;
	int				mvt_x;
	int				mvt_y;
	int				rot;
}					t_config;

typedef struct		s_object
{
	int				type;
	int				face;
	// Delete next
	char			cardinal_face;
	double			hit_location;
	double			distance;
	struct s_object	*next_obj;
}					t_object;

int			cub3d(t_config config);
t_object	*ray(double pos_x, double pos_y, double angle, int **input_map);

// TODO: Delete next line
int		testest(t_config config);

#endif
