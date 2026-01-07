/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/07 17:40:49 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	parse_int(char *in, int *value, t_system *sys)
{
	int	i;
	int	num;

	i = skip_spaces(in);
	if (in[i] == '-')
		error_exit("RGB values must be an int between 0 and 255.\n", sys);
	if (!ft_isdigit(in[i]))
		error_exit("RGB values must be an int between 0 and 255.\n", sys);
	num = ft_atoi(in + i);
	if (num > 255)
		error_exit("RGB values must be an int between 0 and 255.\n", sys);
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}
