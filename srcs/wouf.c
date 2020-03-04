/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wouf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:36:24 by pohl              #+#    #+#             */
/*   Updated: 2020/03/04 20:36:02 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

void		get_hit_info(int face, double vdir, double distance, double pos, t_object *object)
{
	double		hit_location;

	object->face = face;
	hit_location = hit_location - floor(hit_location);
	hit_location = (vdir > 0) ? hit_location : 1 - hit_location;
	object->type = 1;
	object->hit_location = hit_location;
	object->distance = distance;
}

void		get_sprite_info(t_config *cfg, t_2double vdir, t_2int sprite_pos, int type, double angle_ah)
{
	t_2double	cntr;
	t_object	*object;
	double		sp_angl;
	t_2double	ext[2];
	double		ext_angle[2];

	object = &cfg->list->obj[cfg->list->size++];
	object->face = 0;
	object->type = type;

	cntr = (t_2double){sprite_pos.x + 0.5, sprite_pos.y + 0.5};
	double ac = hypot(cfg->pl_pos.x - cntr.x, cfg->pl_pos.y - cntr.y);
	double angle_de = cfg->pl_angle - M_PI_2;
	t_2double d = (t_2double){cntr.x - cos(angle_de) / 2, cntr.y - sin(angle_de) / 2};
	t_2double e = (t_2double){cntr.x + cos(angle_de) / 2, cntr.y + sin(angle_de) / 2};
	double angle_ad = atan2(d.x - cfg->pl_pos.x, d.y - cfg->pl_pos.y);
	double angle_ae = atan2(e.x - cfg->pl_pos.x, e.y - cfg->pl_pos.y);
	printf("ad: %f, ah: %f, ae: %f\r", angle_ad, atan2(vdir.x, vdir.y), angle_ae);
	object->distance = ac;
	object->hit_location = angle_ah - angle_ad / angle_ae - angle_ad;
}

void		ray(t_config *config, double angle)
{
	t_2int		ray_pos;
	int			type;
	t_2double	vdir;
	t_2double	distance;

	vdir.x = 1 / cos(angle);
	vdir.y = 1 / sin(angle);
	ray_pos.x = (int)config->pl_pos.x;
	ray_pos.y = (int)config->pl_pos.y;
	distance.x = (config->pl_pos.x - (int)config->pl_pos.x) * fabs(vdir.x);
	if (vdir.x > 0)
		distance.x = fabs(vdir.x) - distance.x;
	distance.y = (config->pl_pos.y - (int)config->pl_pos.y) * fabs(vdir.y);
	if (vdir.y > 0)
		distance.y = fabs(vdir.y) - distance.y;
	while (config->map[ray_pos.y][ray_pos.x] != 1)
	{
		if (distance.x < distance.y)
		{
			ray_pos.x += (vdir.x < 0) ? -1 : 1;
			type = config->map[ray_pos.y][ray_pos.x];
			if (type == 1 && config->list->size < MAX_OBJ)
				get_hit_info((vdir.x > 0) ? 2 : 0, vdir.y, distance.x, config->pl_pos.y, &config->list->obj[config->list->size++]);
			distance.x += fabs(vdir.x);
		}
		else
		{
			ray_pos.y += (vdir.y < 0) ? -1 : 1;
			type = config->map[ray_pos.y][ray_pos.x];
			if (type == 1 && config->list->size < MAX_OBJ)
				get_hit_info((vdir.y > 0) ? 3 : 1, vdir.x, distance.y, config->pl_pos.x, &config->list->obj[config->list->size++]);
			distance.y += fabs(vdir.y);
		}
		if (type > 1 && config->list->size < MAX_OBJ)
		{
			get_sprite_info(config, vdir, ray_pos, type, angle);
		}
	}
}
