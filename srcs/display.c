/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:41:39 by pohl              #+#    #+#             */
/*   Updated: 2020/02/28 20:50:38 by pohl             ###   ########.fr       */
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

void	reset_screen(int32_t *img_data, int sl, t_config *config)
{
	int		i;

	i = 0;
	while (i < (config->res.y / 2) * sl)
	{
		img_data[i] = config->c_col;
		i++;
	}
	while (i < config->res.y * sl)
	{
		img_data[i] = config->f_col;
		i++;
	}
}

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

int		get_tex(t_config *config, int y, int total_height, t_object *obj)
{
	double	proportion;
	int		face_hit;
	int		result;
	t_2int	img;

	face_hit = (obj->type > 1) ? 4 : obj->face;
	proportion = ((double)y + total_height / 2) / total_height;
	img.y = (int)floor(config->wall[face_hit].size.y * proportion);
	img.x = (int)floor(config->wall[face_hit].size.x * obj->hit_location);
	result =
		config->wall[face_hit].data[img.x + img.y * config->wall[face_hit].sl];
	return (result);
}

int		merge(int new, int old)
{
	t_col	u_col[2];

	u_col[0].i = new;
	u_col[1].i = old;
	u_col[0].c.b = u_col[0].c.b * (1 - u_col[0].c.a / 255.) +
			u_col[1].c.b * ((u_col[0].c.a / 255.) - (u_col[1].c.a / 255.));
	u_col[0].c.g = u_col[0].c.g * (1 - u_col[0].c.a / 255.) +
			u_col[1].c.g * ((u_col[0].c.a / 255.) - (u_col[1].c.a / 255.));
	u_col[0].c.r = u_col[0].c.r * (1 - u_col[0].c.a / 255.) +
			u_col[1].c.r * ((u_col[0].c.a / 255.) - (u_col[1].c.a / 255.));
	u_col[0].c.a = 0;
	return (u_col[0].i);
}

void	draw_column(t_config *conf, t_obj_list *list, int col)
{
	int		pixel;
	int		i;
	int		draw_line;
	int		tex_height;

	while (list->size--)
	{
		draw_line = (int)(conf->res.y / (list->obj[list->size].distance *
			((list->obj[list->size].type > 1) ? 1 : cos(conf->angles[col])))) *
			conf->res.x / conf->res.y;
		tex_height = draw_line;
		if (draw_line > conf->res.y)
			draw_line = conf->res.y;
		i = -draw_line / 2;
		while (i < draw_line / 2)
		{
			pixel = col + (conf->res.y / 2 + i) * conf->img.sl;
			conf->img.data[pixel] = merge(darken(get_tex(conf, i, tex_height,
				&list->obj[list->size]), list->obj[list->size].distance),
				conf->img.data[pixel]);
			(i)++;
		}
	}
}

int		display(t_config *cfg)
{
	int			i;

	apply_movement(cfg);
	reset_screen(cfg->img.data, cfg->img.sl, cfg);
	i = 0;
	while (i < cfg->res.x)
	{
		cfg->list->size = 0;
		ray(cfg->pl_pos, cfg->pl_angle + cfg->angles[i], cfg->map, cfg->list);
		draw_column(cfg, cfg->list, i);
		(i)++;
	}
	mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr, cfg->img.ptr, 0, 0);
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

int		cub3d(t_config *conf)
{
	int		u;

	if (!(conf->win_ptr = mlx_new_window(conf->mlx_ptr,
			conf->res.x, conf->res.y, "Not DOOM")))
		return (-1);
	if (!(conf->list = malloc(sizeof(*conf->list))))
		return (-1);
	conf->img.ptr = mlx_new_image(conf->mlx_ptr, conf->res.x, conf->res.y);
	if (!conf->img.ptr)
		return (-1);
	conf->angles = ray_angles_calculator(M_PI_2, conf->res.x);
	conf->mvt_forward = 0;
	conf->mvt_side = 0;
	conf->rot = 0;
	conf->img.data = (int *)mlx_get_data_addr(conf->img.ptr, &u,
			&conf->img.sl, &u);
	conf->img.sl /= 4;
	mlx_hook(conf->win_ptr, 2, 0, &move, conf);
	mlx_hook(conf->win_ptr, 3, 0, &stop_move, conf);
	mlx_hook(conf->win_ptr, 17, 0, &close_program, conf);
	mlx_loop_hook(conf->mlx_ptr, &display, conf);
	mlx_loop(conf->mlx_ptr);
	return (1);
}
