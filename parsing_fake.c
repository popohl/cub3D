/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fake.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:19:18 by pohl              #+#    #+#             */
/*   Updated: 2020/02/20 17:57:40 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <mlx.h>
#include "cub3d.h"
#include "imgs/r_m1.xpm"
#include "imgs/r_m2.xpm"
#include "imgs/r_m3.xpm"
#include "imgs/r_m4.xpm"
#include "imgs/r_m5.xpm"

int		*ft_arraydup(int *input, size_t size)
{
	size_t	i;
	int		*result_array;

	i = 0;
	if (!(result_array = malloc(sizeof(result_array) * size)))
		return (NULL);
	while (i < size)
	{
		result_array[i] = input[i];
		i++;
	}
	return (result_array);
}

int		main(void)
{
	t_config	config;
	int			useless;
	static int	input_map[14][29] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	// if (!(config.mlx_ptr = mlx_init()))
	// 	return (-1);
	// config.res.x = 1000;
	// config.res.y = 1000;
	// config.f_col = 0x002bfcc4;// 0x00f67280;
	// config.c_col = 0x00355c7d;
	config.map_size.x = 29;
	config.map_size.y = 14;
	if (!(config.map = malloc(sizeof(int **) * config.map_size.x)))
		return (-1);
	for (int i = 0; i < config.map_size.y; i++)
	{
		config.map[i] = ft_arraydup(input_map[i], config.map_size.x);
	}
	config.player_pos.x = 26.5;
	config.player_pos.y = 12.5;
	config.player_angle = 4.71238898038;
	// config.wall[0].ptr = mlx_xpm_to_image(config.mlx_ptr, g_n_texture, &config.wall[0].size.x, &config.wall[0].size.y);
	// config.wall[0].data = (int *)mlx_get_data_addr(config.wall[0].ptr, &useless, &config.wall[0].size_line, &useless);
	// config.wall[0].size_line /= 4;
	// config.wall[1].ptr = mlx_xpm_to_image(config.mlx_ptr, g_s_texture, &config.wall[1].size.x, &config.wall[1].size.y);
	// config.wall[1].data = (int *)mlx_get_data_addr(config.wall[1].ptr, &useless, &config.wall[1].size_line, &useless);
	// config.wall[1].size_line /= 4;
	// config.wall[2].ptr = mlx_xpm_to_image(config.mlx_ptr, g_e_texture, &config.wall[2].size.x, &config.wall[2].size.y);
	// config.wall[2].data = (int *)mlx_get_data_addr(config.wall[2].ptr, &useless, &config.wall[2].size_line, &useless);
	// config.wall[2].size_line /= 4;
	// config.wall[3].ptr = mlx_xpm_to_image(config.mlx_ptr, g_w_texture, &config.wall[3].size.x, &config.wall[3].size.y);
	// config.wall[3].data = (int *)mlx_get_data_addr(config.wall[3].ptr, &useless, &config.wall[3].size_line, &useless);
	// config.wall[3].size_line /= 4;
	// config.wall[4].ptr = mlx_xpm_to_image(config.mlx_ptr, g_sprite_texture, &config.wall[4].size.x, &config.wall[4].size.y);
	// config.wall[4].data = (int *)mlx_get_data_addr(config.wall[4].ptr, &useless, &config.wall[4].size_line, &useless);
	// config.wall[4].size_line /= 4;
	// if (!(config.objects = malloc(sizeof(*config.objects))))
	// 	return (-1);
	cub3d(&config);
	// testest(config);
}

// image_ptr = mlx_xpm_file_to_image(config->mlx_ptr, config->n_texture, &img_width, &img_height);
// 	if (!image_ptr)
// 		return (-1);
// 	imgs[0] = (int *)mlx_get_data_addr(image_ptr, &i[0], &line_size, &i[0]);
// 	line_size /= 4;
