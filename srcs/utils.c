/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:05:23 by pohl              #+#    #+#             */
/*   Updated: 2020/02/17 08:57:07 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

int		darken(int	color, double distance)
{
	unsigned char	c[3];
	int				result;

	distance = 1 - distance / 15;
	if (distance <= 0)
		return (0);
	c[0] = ((unsigned char)(color >> (2 * 8))) * distance;
	c[1] = ((unsigned char)(color >> (1 * 8))) * distance;
	c[2] = ((unsigned char)(color >> (0 * 8))) * distance;
	result = c[0];
	result = result << 8 | c[1];
	result = result << 8 | c[2];
	return (result);
}
