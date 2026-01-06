/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:16 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:16 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	check_lights(char *buffer, t_system *sys)
{
	int				i;
	t_spot_light	*light;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'L' && (i == 0 || buffer[i - 1] == '\n'))
		{
			i++;
			if (sys->light_count >= MAX_LIGHTS)
				error_exit("Too many lights (L).\n", sys);
			light = &sys->light_list[sys->light_count++];
			i += parse_vector3(buffer + i, &light->location, POINT, sys);
			i += parse_float(buffer + i, &light->range, RATIO_0_1, sys);
			i += parse_rgb_color(buffer + i, &light->color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}
