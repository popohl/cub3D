/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:15:37 by pohl              #+#    #+#             */
/*   Updated: 2020/03/01 20:34:14 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include "img.h"

void	write_bmfh(int fd)
{
	int		temp;

	// Header
	write(fd, "BM", 2);
	// file size in bytes
	temp = 54 + 500 * 500 * 4;
	write(fd, &temp, 4);
	// bfReserved1 && bfReserved2
	temp = 0;
	write(fd, &temp, 4);
	// bfOffBits
	temp = 54;
	write(fd, &temp, 4);
}

void	write_bmih(int fd)
{
	int		temp;

	// biSize
	temp = 40;
	write(fd, &temp, 4);
	// biWidth && biHeight
	temp = 500;
	write(fd, &temp, 4);
	temp = 500;
	write(fd, &temp, 4);
	// biPlanes (2B)
	write(fd, "\1\0", 2);
	// biBitCount (2B)
	temp = 32;
	write(fd, &temp, 2);
	// biCompression && biSizeImage && biXPelsPerMeter
	// && biYPelsPerMeter && biClrUsed && biClrImportant
	temp = 0;
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
}

void	write_img(int fd)
{
	write(fd, img, 500 * 500 * 4);
}

int		main(void)
{
	int		fd;

	fd = open("plouf.bmp", O_CREAT | O_WRONLY, S_IRWXU | S_IRGRP | S_IXGRP
					| S_IROTH | S_IXOTH);
	write_bmfh(fd);
	write_bmih(fd);
	write_img(fd);
	return (0);
}
