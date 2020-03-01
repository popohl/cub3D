/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:59:05 by pohl              #+#    #+#             */
/*   Updated: 2020/03/01 18:18:46 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <mlx.h>
#include "cub3d.h"

void		free_all(t_config **conf, int fd)
{
	int	i;

	if (*conf)
	{
		if ((*conf)->mlx_ptr)
		{
			i = -1;
			while (++i < 5)
				if ((*conf)->wall[i].ptr)
					mlx_destroy_image((*conf)->mlx_ptr, (*conf)->wall[i].ptr);
			mlx_destroy_font((*conf)->mlx_ptr);
			free((*conf)->mlx_ptr);
		}
		i = -1;
		while (++i < (*conf)->map_size.y)
			free((*conf)->map[i]);
		free((*conf)->map);
		if ((*conf)->list)
			free((*conf)->list);
		free(*conf);
		*conf = NULL;
		if (fd)
			close(fd);
	}
}

int			error(int code, t_config **config, char *line, int fd)
{
	if (code == 1)
		write(2, "Le nombre d'arguments est incorrect.\n", 37);
	else if (code == 2)
		write(2, "Les arguments de la resolution sont incorrects\n", 47);
	else if (code == 3)
		tex_error(line);
	else if (code == 4)
		color_error(line);
	else if (code == 5)
		write(2, "erreur map_reader\n", 18);
	else
		write(2, "unknown error\n", 14);
	if (line)
		free(line);
	free_all(config, fd);
	return (1);
}

t_config	*initialize_config(void)
{
	t_config	*config;
	int			i;

	if ((config = malloc(sizeof(*config))))
	{
		i = 0;
		while (i < 5)
		{
			config->wall[i].ptr = 0;
			i++;
		}
		config->map = NULL;
		config->map_size = (t_2int){.x = 0, .y = 0};
		config->pl_angle = -1;
		config->f_col = -1;
		config->c_col = -1;
		config->res = (t_2int){.x = 0, .y = 0};
		if ((config->mlx_ptr = mlx_init()))
			return (config);
	}
	free_all(&config, 0);
	return (NULL);
}

void __attribute__((destructor))
			bonjour(void)
{
	// system("leaks cub3d");
	// printf("Et tout est bien qui finit bien !\n");
}

int			analyse_line(char *line, t_config *config, int fd)
{
	if (line[0] == 'R' && read_res(config, line))
		return (error(2, &config, line, fd));
	else if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'E' ||
			line[0] == 'W') && read_tex(config, line))
		return (error(3, &config, line, fd));
	else if ((line[0] == 'F' || line[0] == 'C') && read_col(config, line))
		return (error(4, &config, line, fd));
	else if (line[0] >= '0' && line[0] <= '9' && read_map(config, line))
		return (error(5, &config, line, fd));
	return (0);
}

int			main(int argc, char **argv)
{
	t_config	*config;
	int			i;
	int			fd;
	char		*line;

	if (!(config = initialize_config()))
		return (1);
	fd = argc > 1 ? open(argv[1], O_RDONLY) : -error(1, &config, 0, 0);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (analyse_line(line, config, fd))
			return (1);
		free(line);
	}
	if (fd != -1 && !check_map(config))
		cub3d(config);
	free(line);
	free_all(&config, fd);
	return (0);
}
