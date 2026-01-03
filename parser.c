/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:29 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 12:55:43 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_or_error(t_tuple *vec, t_system *sys)
{
	float	len;

	len = magnitude_vector(vec);
	if (len < EPSILON)
	{
		error_exit("Vector is a zero vector\n", sys);
		return ;
	}
	if (fabsf(len - 1.0f) > 0.01f)
	{
		printf("Warning: vector not normalized \
				(len=%.3f), normalizing...\n", len);
		*vec = normalize_vector(vec);
	}
}

static void	check_objects(char *buffer, t_system *sys)
{
	check_ambient_light(buffer, sys);
	check_camera(buffer, sys);
	sys->light_count = 0;
	check_lights(buffer, sys);
	sys->object_count = 0;
	check_sphere(buffer, sys);
	check_cylinder(buffer, sys);
	check_plane(buffer, sys);
	ft_putstr_fd("Inputfile OK!\n", 1);
}

void	parser(char *input, t_system *sys)
{
	int		fd;
	char	buffer[INFILE_BUFSIZE];
	int		bytes_read;
	char	buffer_overflow;

	if (!check_extension(input))
		error_exit("File must have .rt extension\n", sys);
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open file\n", sys);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (read(fd, &buffer_overflow, 1) > 0)
		error_exit("File is too large\n", sys);
	if (bytes_read < 0)
		error_exit("Cannot read file\n", sys);
	buffer[bytes_read] = '\0';
	close(fd);
	check_objects(buffer, sys);
}
