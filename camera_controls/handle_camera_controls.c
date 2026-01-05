/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_camera_controls.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:07:21 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/04 16:07:34 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	handle_key_wasd(t_app *app, t_system *system, bool *camera_changed)
{
	float	move_speed;

	move_speed = 0.5f;
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
	{
		camera_move(&system->camera, 0, 0, move_speed);
		*camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_E))
	{
		camera_move(&system->camera, 0, 0, -move_speed);
		*camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_Q))
	{
		camera_move(&system->camera, move_speed, 0, 0);
		*camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_R))
	{
		camera_move(&system->camera, -move_speed, 0, 0);
		*camera_changed = true;
	}
}

static void	handle_key_ty(t_app *app, t_system *system, bool *camera_changed)
{
	float	move_speed;

	move_speed = 0.5f;
	if (mlx_is_key_down(app->mlx, MLX_KEY_T))
	{
		camera_move(&system->camera, 0, move_speed, 0);
		*camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
	{
		camera_move(&system->camera, 0, -move_speed, 0);
		*camera_changed = true;
	}
}

static void	handle_key_upx(t_app *app, t_system *system, bool *camera_changed)
{
	float	rotate_speed;

	rotate_speed = 0.1f;
	if (mlx_is_key_down(app->mlx, MLX_KEY_U))
	{
		camera_rotate_yaw(&system->camera, -rotate_speed);
		*camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_P))
	{
		camera_rotate_yaw(&system->camera, rotate_speed);
		*camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
	{
		camera_reset(&system->camera);
		*camera_changed = true;
	}
}

void	handle_camera_controls(t_app *app, t_system *system)
{
	bool	camera_changed;

	camera_changed = false;
	handle_key_wasd(app, system, &camera_changed);
	handle_key_ty(app, system, &camera_changed);
	handle_key_upx(app, system, &camera_changed);
	if (camera_changed)
	{
		camera_update_transform(&system->camera);
		system->state &= ~RENDER_COMPLETE;
		system->state &= ~DRAFT_RENDERED;
		system->render_line = 0;
	}
}
