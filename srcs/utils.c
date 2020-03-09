/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:05:23 by pohl              #+#    #+#             */
/*   Updated: 2020/03/09 15:11:25 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "cub3d.h"

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

void	color_error(char *line)
{
	if (*line == 'F')
		write(2, "Wrong formatting for the floor color parameter.\n", 48);
	else
		write(2, "Wrong formatting for the ceiling color parameter.\n", 50);
}

void	tex_error(char *line)
{
	if (*line == 'N')
		write(2, "The North texture is invalid.\n", 30);
	else if (*line == 'S' && line[1] == 'O')
		write(2, "The South texture is invalid.\n", 30);
	else if (*line == 'E')
		write(2, "The East texture is invalid.\n", 29);
	else if (*line == 'W')
		write(2, "The West texture is invalid.\n", 29);
	else if (*line == 'S')
		write(2, "The Sprite texture is invalid.\n", 31);
	else
		write(2, "The identifier is invalid.\n", 27);
}
