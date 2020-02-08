/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:41:39 by pohl              #+#    #+#             */
/*   Updated: 2020/02/08 21:53:49 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../cub3d.h"

int		close_program(t_config *params)
{
	mlx_destroy_window(params->mlx_ptr, params->win_ptr);
	exit(1);
	return (0);
}

void	reset_screen(int32_t **img_data, int size_line, t_config *config)
{
	int		i;

	i = 0;
	while (i < config->y_res * size_line)
	{
		(*img_data)[i] = 0;
		i++;
	}
	i = 0;
	while (i < (config->y_res / 2) * size_line)
	{
		(*img_data)[i] = config->c_col;
		i++;
	}
	while (i < config->y_res * size_line)
	{
		(*img_data)[i] = config->f_col;
		i++;
	}
}

int		move(int keycode, t_config *config)
{
	if (keycode == 13)
		config->mvt_y -= 1;
	if (keycode == 1)
		config->mvt_y += 1;
	if (keycode == 0)
		config->mvt_x -= 1;
	if (keycode == 2)
		config->mvt_x += 1;
	if (keycode == 123 || keycode == 12)
		config->rot -= 1;
	if (keycode == 124 || keycode == 14)
		config->rot += 1;
	return (1);
}

int		stop_move(int keycode, t_config *config)
{
	if (keycode == 13)
		config->mvt_y = 0;
	if (keycode == 1)
		config->mvt_y = 0;
	if (keycode == 0)
		config->mvt_x = 0;
	if (keycode == 2)
		config->mvt_x = 0;
	if (keycode == 123 || keycode == 12)
		config->rot = 0;
	if (keycode == 124 || keycode == 14)
		config->rot = 0;
	if (keycode == 53)
		close_program(config);
	return (1);
}

int		display(t_config *config)
{
	int			*img_data;
	int			draw_line;
	int			i[6];
	int			line_size, u1, u2;
	t_object	*objects;

	if (config->mvt_x > 0)
		config->player_posx += 0.05;
	else if (config->mvt_x < 0)
		config->player_posx -= 0.05;
	if (config->mvt_y > 0)
		config->player_posy += 0.05;
	else if (config->mvt_y < 0)
		config->player_posy -= 0.05;
	if (config->rot > 0)
		config->player_angle += 0.05;
	else if (config->rot < 0)
		config->player_angle -= 0.05;
	img_data = (int *)mlx_get_data_addr(config->img_ptr, &u1, &line_size, &u2);
	line_size /= 4;
	reset_screen(&img_data, line_size, config);
	i[0] = 0;
	while (i[0] < config->x_res)
	{
		objects = ray(config->player_posx, config->player_posy, config->player_angle + config->angles[i[0]], config->map);
		while (objects)
		{
			draw_line = (int)(config->y_res * 1 / (objects->distance * cos(config->angles[i[0]])));
			if (draw_line > config->y_res)
				draw_line = config->y_res;
			i[1] = 0;
			while (i[1] < draw_line)
			{
				i[3] = i[0] + (config->y_res / 2 - draw_line / 2 + i[1]) * line_size;
				if (objects->type == 1)
					img_data[i[3]] = 0x002bfcc4;
				else
					img_data[i[3]] = 0x006bdf4a;
				(i[1])++;
			}
			objects = objects->next_obj;
		}
		(i[0])++;
	}
	mlx_put_image_to_window(config->mlx_ptr, config->win_ptr, config->img_ptr, 0, 0);
	return (0);
}

double	*ray_angles_calculator(double fov, int screen_width)
{
	double	virtual_width;
	double	ratio;
	double	*angle_table;
	int		i;

	if (!(angle_table = malloc(sizeof(*angle_table) * screen_width)))
		return (NULL);
	virtual_width = fov / M_PI_2;
	i = 0;
	while (i < screen_width)
	{
		ratio = i / (double)screen_width - 0.5;
		angle_table[i] = atan(ratio * virtual_width);
		i++;
	}
	return (angle_table);
}

int		cub3d(t_config config)
{
	void *mlx_ptr;
	void *win_ptr;

	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(win_ptr = mlx_new_window(mlx_ptr,
			config.x_res, config.y_res, "Not DOOM")))
		return (-1);
	config.mlx_ptr = mlx_ptr;
	config.win_ptr = win_ptr;
	config.img_ptr = mlx_new_image(config.mlx_ptr, config.x_res, config.y_res);
	config.angles = ray_angles_calculator(M_PI_2, config.x_res);
	config.mvt_x = 0;
	config.mvt_y = 0;
	config.rot = 0;
	mlx_hook(win_ptr, 2, 0, &move, &config);
	mlx_hook(win_ptr, 3, 0, &stop_move, &config);
	mlx_hook(win_ptr, 17, 0, &close_program, &config);
	mlx_loop_hook(config.mlx_ptr, &display, &config);
	mlx_loop(mlx_ptr);
	return (1);
}
