/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_commas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:08 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:08 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	skip_commas(char *buffer, t_system *sys)
{
	int	i;

	i = 0;
	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	if (buffer[i] != ',')
		error_exit("Expected comma between components.\n", sys);
	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	return (i + 1);
}
