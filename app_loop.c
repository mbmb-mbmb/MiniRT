#include "minirt.h"

static void	draft_transformations(t_system *sys)
{
	(void)sys;
}

static void	handle_camera_controls(t_app *app, t_system *system)
{
	bool	camera_changed;
	float	move_speed;
	float	rotate_speed;

	camera_changed = false;
	move_speed = 0.5f;
	rotate_speed = 0.1f;
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
	{
		camera_move(&system->camera, 0, 0, move_speed);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_E))
	{
		camera_move(&system->camera, 0, 0, -move_speed);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_Q))
	{
		camera_move(&system->camera, move_speed, 0, 0);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_R))
	{
		camera_move(&system->camera, -move_speed, 0, 0);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_T))
	{
		camera_move(&system->camera, 0, move_speed, 0);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
	{
		camera_move(&system->camera, 0, -move_speed, 0);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_U))
	{
		camera_rotate_yaw(&system->camera, -rotate_speed);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_P))
	{
		camera_rotate_yaw(&system->camera, rotate_speed);
		camera_changed = true;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
	{
		camera_reset(&system->camera);
		camera_changed = true;
	}
	if (camera_changed)
	{
		camera_update_transform(&system->camera);
		system->state &= ~RENDER_COMPLETE;
	}
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
		{
			render(system, app->img);
			system->state |= RENDER_COMPLETE;
		}
	}
	else
		mlx_close_window(app->mlx);
}
