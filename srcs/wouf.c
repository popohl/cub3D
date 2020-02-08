/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wouf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:36:24 by pohl              #+#    #+#             */
/*   Updated: 2020/02/08 17:35:29 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../cub3d.h"

const char cardinal_points[5] = "ONES";

void		objects_addfront(t_object **list, t_object *new_item)
{
	new_item->next_obj = *list;
	*list = new_item;
}

t_object	*get_hit_info(int face, double vdir, double distance, double pos, int type)
{
	double		hit_location;
	t_object	*hit_object;

	if (!(hit_object = malloc(sizeof(*hit_object))))
		return(0);
	hit_object->face = (vdir > 0) ? face + 2 : face;
	hit_location = distance / fabs(vdir) + pos;
	hit_location = 1 - hit_location + floor(hit_location);
	hit_object->hit_location = hit_location;
	hit_object->distance = distance;
	hit_object->cardinal_face = cardinal_points[hit_object->face];
	hit_object->type = type;
	hit_object->next_obj = 0;
	return hit_object;
}

t_object	*ray(double pos_x, double pos_y, double angle, int **input_map)
{
	int			ray_pos[2];
	int			type;
	double		vdir[2];
	double		distance[2];
	t_object	*objects;

	objects = 0;
	ray_pos[0] = (int)pos_x;
	ray_pos[1] = (int)pos_y;
	vdir[0] = 1 / cos(angle);
	vdir[1] = 1 / sin(angle);
	distance[0] = (pos_x - (int)pos_x) * fabs(vdir[0]);
	if (vdir[0] > 0)
		distance[0] = fabs(vdir[0]) - distance[0];
	distance[1] = (pos_y - (int)pos_y) * fabs(vdir[1]);
	if (vdir[1] > 0)
		distance[1] = fabs(vdir[1]) - distance[1];
	while (input_map[ray_pos[1]][ray_pos[0]] != 1)
	{
		if (distance[0] < distance[1])
		{
			ray_pos[0] += (vdir[0] < 0) ? -1 : 1;
			type = input_map[ray_pos[1]][ray_pos[0]];
			if (type)
				objects_addfront(&objects, get_hit_info(0, vdir[1], distance[0], pos_x, type));
			distance[0] += fabs(vdir[0]);
		}
		else
		{
			ray_pos[1] += (vdir[1] < 0) ? -1 : 1;
			type = input_map[ray_pos[1]][ray_pos[0]];
			if (type)
				objects_addfront(&objects, get_hit_info(1, vdir[0], distance[1], pos_y, type));
			distance[1] += fabs(vdir[1]);
		}
	}
	return (objects);
}
