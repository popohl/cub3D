/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wouf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:36:24 by pohl              #+#    #+#             */
/*   Updated: 2020/02/28 19:14:02 by pohl             ###   ########.fr       */
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
	hit_location = distance / fabs(vdir) + (vdir < 0 ? 1 - (pos - floor(pos)) : (pos - floor(pos)));
	hit_location = hit_location - floor(hit_location);
	hit_location = (vdir > 0) ? hit_location : 1 - hit_location;
	object->type = 1;
	object->hit_location = hit_location;
	object->distance = distance;
}

void		get_sprite_info(t_2double vdir, t_2int sprite_pos, t_2double play_pos, int type, t_object *object)
{
	t_2double	center;
	t_2double	extrem_it[2];
	double		ray_angle[3];

	center = (t_2double){sprite_pos.x + 0.5, sprite_pos.y + 0.5};
	if (vdir.x * vdir.y > 0)
	{
		extrem_it[0] = (t_2double){center.x + .5, center.y - .5};
		extrem_it[1] = (t_2double){center.x - .5, center.y + .5};
	}
	else
	{
		extrem_it[0] = (t_2double){center.x + .5, center.y + .5};
		extrem_it[1] = (t_2double){center.x - .5, center.y - .5};
	}
	ray_angle[0] = (vdir.y < 0 ? -1 : 1) * acos(1 / vdir.x) + M_PI;
	ray_angle[1] = 2 * (M_PI_2 - atan((extrem_it[0].x - play_pos.x) / (extrem_it[0].y - play_pos.y)));
	ray_angle[2] = 2 * (M_PI_2 - atan((extrem_it[1].x - play_pos.x) / (extrem_it[1].y - play_pos.y)));
	if (ray_angle[2] > ray_angle[1])
		object->hit_location = (ray_angle[0] - ray_angle[1]) / (ray_angle[2] - ray_angle[1]);
	else
		object->hit_location = (ray_angle[0] - ray_angle[2]) / (ray_angle[1] - ray_angle[2]);
	if (ray_angle[0] < fmin(ray_angle[1], ray_angle[2]) || ray_angle[0] > fmax(ray_angle[1], ray_angle[2]))
		object->hit_location = 0.5;
	// printf("%f, %f, %f \r", ray_angle[1], ray_angle[0], ray_angle[2]);
	// DF();
	// DF(ray_angle[0]);
	// DF(ray_angle[2]);
	// exit(1);
	object->face = 0;
	object->type = type;
	object->distance = hypot(play_pos.x - center.x, play_pos.y - center.y);
}

void		ray(t_2double pos, double angle, char **map, t_obj_list *list)
{
	t_2int		ray_pos;
	int			type;
	t_2double	vdir;
	t_2double	distance;

	vdir.x = 1 / cos(angle);
	vdir.y = 1 / sin(angle);
	ray_pos.x = (int)pos.x;
	ray_pos.y = (int)pos.y;
	distance.x = (pos.x - (int)pos.x) * fabs(vdir.x);
	if (vdir.x > 0)
		distance.x = fabs(vdir.x) - distance.x;
	distance.y = (pos.y - (int)pos.y) * fabs(vdir.y);
	if (vdir.y > 0)
		distance.y = fabs(vdir.y) - distance.y;
	while (map[ray_pos.y][ray_pos.x] != 1)
	{
		if (distance.x < distance.y)
		{
			ray_pos.x += (vdir.x < 0) ? -1 : 1;
			type = map[ray_pos.y][ray_pos.x];
			if (type == 1 && list->size < MAX_OBJ)
				get_hit_info((vdir.x > 0) ? 2 : 0, vdir.y, distance.x, pos.y, &list->obj[list->size++]);
			distance.x += fabs(vdir.x);
		}
		else
		{
			ray_pos.y += (vdir.y < 0) ? -1 : 1;
			type = map[ray_pos.y][ray_pos.x];
			if (type == 1 && list->size < MAX_OBJ)
				get_hit_info((vdir.y > 0) ? 3 : 1, vdir.x, distance.y, pos.x, &list->obj[list->size++]);
			distance.y += fabs(vdir.y);
		}
		if (type > 1 && list->size < MAX_OBJ)
			get_sprite_info(vdir, ray_pos, pos, type, &list->obj[list->size++]);
	}
}
