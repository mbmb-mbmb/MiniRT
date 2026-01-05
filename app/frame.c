/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:16:25 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:40:02 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	draft_transformations(t_system *sys)
{
	(void)sys;
}

static void	render_scene(t_system *sys, mlx_image_t *img)
{
	render(sys, img);
}

void	frame(void *param)
{
	t_app		*app;
	t_system	*system;

	app = (t_app *)param;
	system = &app->system;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		system->state |= SHOULD_EXIT;
	if (!(system->state & SHOULD_EXIT))
	{
		handle_camera_controls(app, system);
		if (system->state & DRAFT_MODE)
			draft_transformations(system);
		if (!(system->state & RENDER_COMPLETE))
			render_scene(system, app->img);
	}
	else
		mlx_close_window(app->mlx);
}
