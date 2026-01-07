/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:29 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:44:29 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
	if(sys->object_count == 0)
		error_exit("A scene needs at least one object.\n", sys);
	ft_putstr_fd("Inputfile OK!\n", 1);
}

void	parser(char *input, t_system *sys)
{
	int		fd;
	char	buffer[INFILE_BUFSIZE];
	int		bytes_read;
	char	buffer_overflow;

	sys->state |= PARSING;
	if (!validate_rt_file_extension(input))
		error_exit("File must have a name and a .rt extension.\n", sys);
	sys->parser_fd = -1;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open file.\n", sys);
	sys->parser_fd = fd;
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (read(fd, &buffer_overflow, 1) > 0)
		error_exit("File is too large.\n", sys);
	if (bytes_read < 0)
		error_exit("Cannot read file.\n", sys);
	buffer[bytes_read] = '\0';
	close(fd);
	sys->parser_fd = -1;
	check_objects(buffer, sys);
}
