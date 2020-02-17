/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:41:39 by pohl              #+#    #+#             */
/*   Updated: 2020/02/17 13:53:11 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cub3d.h"

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
	while (i < config->res.y * size_line)
	{
		(*img_data)[i] = 0;
		i++;
	}
	i = 0;
	while (i < (config->res.y / 2) * size_line)
	{
		(*img_data)[i] = config->c_col;
		i++;
	}
	while (i < config->res.y * size_line)
	{
		(*img_data)[i] = config->f_col; //darken(config->f_col, atanh(2 - ((double)i / (config->res.y / 2 * size_line))) / 1.68 * 10);
		i++;
	}
}

int		move(int keycode, t_config *config)
{
	if (keycode == 13 && !config->mvt_forward)
		config->mvt_forward = 1;
	if (keycode == 1 && !config->mvt_forward)
		config->mvt_forward = -1;
	if (keycode == 0 && !config->mvt_sideways)
		config->mvt_sideways = 1;
	if (keycode == 2 && !config->mvt_sideways)
		config->mvt_sideways = -1;
	if (keycode == 123 || keycode == 12)
		config->rot -= 1;
	if (keycode == 124 || keycode == 14)
		config->rot += 1;
	return (1);
}

int		stop_move(int keycode, t_config *config)
{
	if (keycode == 13)
		config->mvt_forward = 0;
	if (keycode == 1)
		config->mvt_forward = 0;
	if (keycode == 0)
		config->mvt_sideways = 0;
	if (keycode == 2)
		config->mvt_sideways = 0;
	if (keycode == 123 || keycode == 12)
		config->rot = 0;
	if (keycode == 124 || keycode == 14)
		config->rot = 0;
	if (keycode == 53)
		close_program(config);
	return (1);
}

void	apply_movement(t_config *config)
{
	double	speed;
	double	new_pos_x;
	double	new_pos_y;

	speed = 0.05;
	new_pos_x = config->player_pos.x;
	new_pos_y = config->player_pos.y;
	if (config->mvt_forward)
	{
		new_pos_x += cos(config->player_angle) * speed * config->mvt_forward;
		new_pos_y += sin(config->player_angle) * speed * config->mvt_forward;
	}
	if (config->mvt_sideways)
	{
		new_pos_x += cos(config->player_angle - M_PI_2) * speed * config->mvt_sideways;
		new_pos_y += sin(config->player_angle - M_PI_2) * speed * config->mvt_sideways;
	}
	if (config->map[(int)floor(config->player_pos.y)][(int)floor(new_pos_x)] != 1)
		config->player_pos.x = new_pos_x;
	if (config->map[(int)floor(new_pos_y)][(int)floor(config->player_pos.x)] != 1)
		config->player_pos.y = new_pos_y;
	if (config->rot > 0)
		config->player_angle += 0.02;
	else if (config->rot < 0)
		config->player_angle -= 0.02;
}

int		get_tex(t_config *config, int y, int total_height, t_object *obj)
{
	double	proportion;
	int		face_hit;
	t_2int	img;

	face_hit = (obj->type > 1) ? 4 : obj->face;
	proportion = ((double)y + total_height / 2) / total_height;
	img.y = (int)floor(config->wall[face_hit].size.y * proportion);
	img.x = (int)floor(config->wall[face_hit].size.x * obj->hit_location);
	return (config->wall[face_hit].data[img.x + img.y * config->wall[face_hit].size_line]);
}

int		display(t_config *config)
{
	int			*img_data;
	int			draw_line;
	int			i[6];
	int			line_size;
	t_obj_list	*list;

	apply_movement(config);
	img_data = (int *)mlx_get_data_addr(config->img_ptr, &i[0], &line_size, &i[0]);
	line_size /= 4;
	reset_screen(&img_data, line_size, config);
	if (!(list = malloc(sizeof(*list))))
		return (-1);
	i[0] = 0;
	while (i[0] < config->res.x)
	{
		list->size = 0;
		ray(config->player_pos, config->player_angle + config->angles[i[0]], config->map, list);
		while (list->size--)
		{
			draw_line = (int)(config->res.y / (list->obj[list->size].distance * ((list->obj[list->size].type > 1) ? 1 : cos(config->angles[i[0]]))));
			i[5] = draw_line;
			if (draw_line > config->res.y)
				draw_line = config->res.y;
			i[1] = -draw_line / 2;
			while (i[1] < draw_line / 2)
			{
				i[3] = i[0] + (config->res.y / 2 + i[1]) * line_size;
				if (list->obj[list->size].type)
					img_data[i[3]] = darken(get_tex(config, i[1], i[5], &list->obj[list->size]), list->obj[list->size].distance);
				// else
				// 	img_data[i[3]] = darken(0x006bdf4a, list->obj[list->size].distance);
				(i[1])++;
			}
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

int		cub3d(t_config *config)
{

	if (!(config->win_ptr = mlx_new_window(config->mlx_ptr,
			config->res.x, config->res.y, "Not DOOM")))
		return (-1);
	config->img_ptr = mlx_new_image(config->mlx_ptr, config->res.x, config->res.y);
	config->angles = ray_angles_calculator(M_PI_2, config->res.x);
	config->mvt_forward = 0;
	config->mvt_sideways = 0;
	config->rot = 0;
	mlx_hook(config->win_ptr, 2, 0, &move, config);
	mlx_hook(config->win_ptr, 3, 0, &stop_move, config);
	mlx_hook(config->win_ptr, 17, 0, &close_program, config);
	mlx_loop_hook(config->mlx_ptr, &display, config);
	mlx_loop(config->mlx_ptr);
	return (1);
}
