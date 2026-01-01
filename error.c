/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:12:26 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/01 12:00:02 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./miniRT <scene.rt>\n", 2);
	ft_putstr_fd("\nScene file format:\n", 2);
	ft_putstr_fd("A  <ratio>  <R,G,B>\n", 2);
	ft_putstr_fd("C  <x,y,z>  <nx,ny,nz>  <fov>\n", 2);
	ft_putstr_fd("L  <x,y,z>  <ratio>  <R,G,B>\n", 2);
	ft_putstr_fd("sp <x,y,z>  <diameter>  <R,G,B>\n", 2);
	ft_putstr_fd("pl <x,y,z>  <nx,ny,nz>  <R,G,B>\n", 2);
	ft_putstr_fd("cy <x,y,z>  <nx,ny,nz>  <dia>  <height>  <R,G,B>\n", 2);
}

void	error_exit(char *msg, t_system *sys)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		print_usage();
	if (sys)
	{
		sys->exit_code = 1;
		sys->state |= SHOULD_EXIT;
	}
	exit(1);
}
