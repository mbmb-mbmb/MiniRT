#ifndef MINIRT_H
# define MINIRT_H

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 256
#define HEIGHT 256


typedef struct	s_amb_light
{
	double		range;
	uint32_t	rgb;
	
}	t_amb_light;

typedef struct	s_data
{
	t_amb_light	amb_light;
	
}	t_data;

void	rt_parser(char *input, t_data *data);


#endif