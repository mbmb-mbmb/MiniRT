/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:45:07 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:45:13 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	parse_fov(char *in, int *value, t_system *sys)
{
	int	i;
	int	num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < 0 || num > 180)
		error_exit("FOV must be between 0 and 180 degrees.\n", sys);
	if (num == 0)
		num = 1;
	if (num == 180)
		num = 179;
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}
