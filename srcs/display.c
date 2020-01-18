/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:41:39 by pohl              #+#    #+#             */
/*   Updated: 2020/01/18 19:02:04 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc -lmlx -framework OpenGL -framework AppKit plouf.c mlx/libmlx.a

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "../cub3d.h"

int		printer(int keycode, t_config *config)
{
	char		*str_kc;

	str_kc = ft_itoa(keycode);
	mlx_clear_window(config->mlx_ptr, config->win_ptr);
	mlx_string_put(config->mlx_ptr, config->win_ptr, 50, 50, config->c_col, str_kc);
	return (0);
}

int		cub3d(t_config config)
{
	void		*mlx_ptr;
	void		*win_ptr;

	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Plouf <3")))
		return (-1);
	config.mlx_ptr = mlx_ptr;
	config.win_ptr = win_ptr;
	mlx_key_hook(win_ptr, &printer, &config);
	mlx_loop(mlx_ptr);
	return (1);
}
