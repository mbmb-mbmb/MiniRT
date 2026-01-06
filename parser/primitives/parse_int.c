/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:39 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	parse_int(char *in, int *value, t_system *sys)
{
	int	i;
	int	num;

	i = skip_spaces(in);
	num = ft_atoi(in + i);
	if (num < 0 || num > 255)
		error_exit("RGB values must be between 0 and 255.\n", sys);
	*value = num;
	while (in[i] == '-' || in[i] == '+' || ft_isdigit(in[i]))
		i++;
	return (i);
}
