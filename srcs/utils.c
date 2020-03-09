/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:05:23 by pohl              #+#    #+#             */
/*   Updated: 2020/03/09 18:58:18 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "cub3d.h"

/*
** darken will fade the color given in parameter using the distance from the
** player, the further away it is, the darker the color get until it's
** completely black, at a distance of 15 blocks.
*/

int		darken(int color, double distance)
{
	unsigned char	c[4];
	int				result;

	distance = 1 - distance / 15;
	c[0] = ((unsigned char)(color >> (3 * 8)));
	if (distance <= 0 && c[0] == 0xff)
		return (0xff000000);
	if (distance <= 0)
		return (0);
	c[1] = ((unsigned char)(color >> (2 * 8))) * distance;
	c[2] = ((unsigned char)(color >> (1 * 8))) * distance;
	c[3] = ((unsigned char)(color >> (0 * 8))) * distance;
	result = c[0];
	result = result << 8 | c[1];
	result = result << 8 | c[2];
	result = result << 8 | c[3];
	return (result);
}

/*
** prints the map in the command line.
** converts the characters to "readable" ones, i.e. '\0' becomes '0'
*/

int		print_map(char **map, t_2int map_size)
{
	int		i;
	int		j;
	char	to_write;

	i = 0;
	while (i < map_size.y)
	{
		j = 0;
		while (j < map_size.x)
		{
			to_write = map[i][j] + '0';
			write(1, &to_write, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n\n", 2);
	return (0);
}

/*
** count_digits counts the number of digits in 'str',
** returns -1 if it comes along an invalid character
** returns the digit_count otherwise
*/

int		count_digits(char *str, int *width)
{
	int		i;
	int		digit_count;

	i = 0;
	digit_count = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '2') || str[i] == 'N' || str[i] == 'S'
				|| str[i] == 'E' || str[i] == 'W' || str[i] == ' ')
			digit_count++;
		else
			return (-1);
		i++;
	}
	*width = digit_count;
	return (digit_count ? 0 : -1);
}

/*
** merge combines 2 pixels using their transparency value.
*/

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

/*
** get_tex returns the color of an image's pixel given it's position in x and y
*/

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
	if (obj->hit_location < 0)
		result = 0xff000000;
	return (result);
}
