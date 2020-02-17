/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:16:35 by pohl              #+#    #+#             */
/*   Updated: 2020/02/17 05:35:48 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "cub3d.h"

void	ray(t_2double pos, double angle, int **input_map, t_obj_list *list);

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

	if (!(result = malloc(sizeof(*result) * 20)))
		return (2);
	while(i < 20)
	{
		// ray(25.50, 11.1, 1.941593 + angle_table[i], config.map, &result[i]);
		// printf("result: distance : %f ; Face: %c\n", result[i].distance, result[i].cardinal_face);
		// if (result[i].next)
		// {
		// 	ft_objclear(&(result[i].next));
		// 	if(result[i].next)
		// 		printf("Fuck\n");
		// }
		i++;
	}
	free(angle_table);
	angle_table = 0;
	return (0);
}
