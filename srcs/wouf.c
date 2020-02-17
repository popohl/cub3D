/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wouf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:36:24 by pohl              #+#    #+#             */
/*   Updated: 2020/02/17 14:23:01 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

const char cardinal_points[5] = "ONES";

void		get_hit_info(int face, double vdir, double distance, double pos, int type, t_object *object)
{
	double		hit_location;

	object->face = face;
	hit_location = distance / fabs(vdir) + (vdir < 0 ? 1 - (pos - floor(pos)) : (pos - floor(pos)));
	hit_location = hit_location - floor(hit_location);
	object->hit_location = (vdir > 0 && !(type > 1)) ? hit_location : 1 - hit_location;
	object->distance = distance;
	object->cardinal_face = cardinal_points[object->face];
	object->type = type;
}

void		ray(t_2double pos, double angle, int **input_map, t_obj_list *list)
{
	t_2int		ray_pos;
	int			type;
	t_2double	vdir;
	t_2double	distance;

	ray_pos.x = (int)pos.x;
	ray_pos.y = (int)pos.y;
	vdir.x = 1 / cos(angle);
	vdir.y = 1 / sin(angle);
	distance.x = (pos.x - (int)pos.x) * fabs(vdir.x);
	if (vdir.x > 0)
		distance.x = fabs(vdir.x) - distance.x;
	distance.y = (pos.y - (int)pos.y) * fabs(vdir.y);
	if (vdir.y > 0)
		distance.y = fabs(vdir.y) - distance.y;
	while (input_map[ray_pos.y][ray_pos.x] != 1)
	{
		if (distance.x < distance.y)
		{
			ray_pos.x += (vdir.x < 0) ? -1 : 1;
			type = input_map[ray_pos.y][ray_pos.x];
			if (type == 1)
				get_hit_info((vdir.x > 0) ? 2 : 0, vdir.y, distance.x, pos.y, type, &list->obj[list->size++]);
			else if (type > 1)
				get_hit_info((vdir.x > 0) ? 2 : 0, vdir.y, sqrt((pos.x - (ray_pos.x + .5)) * (pos.x - (ray_pos.x + .5)) + (pos.y - (ray_pos.y + .5)) * (pos.y - (ray_pos.y + .5))), pos.y, type, &list->obj[list->size++]);
			distance.x += fabs(vdir.x);
		}
		else
		{
			ray_pos.y += (vdir.y < 0) ? -1 : 1;
			type = input_map[ray_pos.y][ray_pos.x];
			if (type == 1)
				get_hit_info((vdir.y > 0) ? 3 : 1, vdir.x, distance.y, pos.x, type, &list->obj[list->size++]);
			else if (type > 1)
				get_hit_info((vdir.x > 0) ? 3 : 1, vdir.x, sqrt((pos.x - (ray_pos.x + .5)) * (pos.x - (ray_pos.x + .5)) + (pos.y - (ray_pos.y + .5)) * (pos.y - (ray_pos.y + .5))), pos.x, type, &list->obj[list->size++]);
			distance.y += fabs(vdir.y);
		}
	}
}
