/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:45:21 by pohl              #+#    #+#             */
/*   Updated: 2020/03/09 18:52:57 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		move(int keycode, t_config *config)
{
	if (keycode == 13 && !config->mvt_forward)
		config->mvt_forward = 1;
	if (keycode == 1 && !config->mvt_forward)
		config->mvt_forward = -1;
	if (keycode == 0 && !config->mvt_side)
		config->mvt_side = 1;
	if (keycode == 2 && !config->mvt_side)
		config->mvt_side = -1;
	if (keycode == 123 || keycode == 12)
		config->rot -= 1;
	if (keycode == 124 || keycode == 14)
		config->rot += 1;
	if (keycode == 4)
		if (create_img(config->res.x, config->res.y, config->img.data))
			close_program(config);
	return (1);
}

int		stop_move(int keycode, t_config *config)
{
	if (keycode == 13)
		config->mvt_forward = 0;
	if (keycode == 1)
		config->mvt_forward = 0;
	if (keycode == 0)
		config->mvt_side = 0;
	if (keycode == 2)
		config->mvt_side = 0;
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
	new_pos_x = config->pl_pos.x;
	new_pos_y = config->pl_pos.y;
	if (config->mvt_forward)
	{
		new_pos_x += cos(config->pl_angle) * speed * config->mvt_forward;
		new_pos_y += sin(config->pl_angle) * speed * config->mvt_forward;
	}
	if (config->mvt_side)
	{
		new_pos_x += cos(config->pl_angle - M_PI_2) * speed * config->mvt_side;
		new_pos_y += sin(config->pl_angle - M_PI_2) * speed * config->mvt_side;
	}
	if (config->map[(int)floor(config->pl_pos.y)][(int)floor(new_pos_x)] != 1)
		config->pl_pos.x = new_pos_x;
	if (config->map[(int)floor(new_pos_y)][(int)floor(config->pl_pos.x)] != 1)
		config->pl_pos.y = new_pos_y;
	if (config->rot > 0)
		config->pl_angle += M_PI / 64;
	else if (config->rot < 0)
		config->pl_angle -= M_PI / 64;
}
