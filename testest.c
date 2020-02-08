/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:16:35 by pohl              #+#    #+#             */
/*   Updated: 2020/02/08 14:03:17 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "cub3d.h"

t_object	*ray(double pos_x, double pos_y, double angle, int **input_map);

// Calculer l'écart d'angle entre chaque ray envoyé :
double	*rayAnglesCalculator(double fov, int screen_width)
{
	double	virtual_width;
	double	ratio;
	double	*angle_table;
	int		i;

	if (!(angle_table = malloc(sizeof(*angle_table) * screen_width)))
		return (NULL);
	virtual_width = fov / (M_PI / 2);
	i = 0;
	while (i < screen_width)
	{
		ratio = i / (double)screen_width - 0.5;
		angle_table[i] = atan(ratio * virtual_width);
		i++;
	}
	return (angle_table);
}

int		testest(t_config config)
{
	double		*angle_table = rayAnglesCalculator(M_PI_4, 20);
	t_object	*result;
	int		i = 0;

	while(i < 20)
	{
		result = ray(25.50, 11.1, 1.941593 + angle_table[i], config.map);
		printf("result: distance : %f ; Face: %c\n", result->distance, result->cardinal_face);
		i++;
	}
	return (0);
}
