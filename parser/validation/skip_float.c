/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:09 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:09 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	skip_float(char *buffer)
{
	int	i;

	i = 0;
	if (buffer[i] == '-' || buffer[i] == '+')
		i++;
	while (buffer[i] && (ft_isdigit(buffer[i]) || buffer[i] == '.'))
		i++;
	return (i);
}
