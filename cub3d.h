/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:35:29 by pohl              #+#    #+#             */
/*   Updated: 2020/01/17 13:09:13 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

typedef void* ptr;

typedef struct 	s_var_array
{
	ptr		**data;
	size_t	size;
	size_t	max_size;
	size_t	push_size;
}				t_var_array;


typedef struct	s_config
{
	int			x_resoltion;
	int			y_resoltion;
	char		*n_texture;
	char		*s_texture;
	char		*e_texture;
	char		*w_texture;
	char		*sprite_texture;
	int32_t		floor_color;
	int32_t		c_col;
	int			**map;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_config;

int		cub3d(t_config config);

#endif
