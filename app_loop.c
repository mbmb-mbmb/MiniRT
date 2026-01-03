#include "minirt.h"

static void	draft_transformations(t_system *sys)
{
	(void)sys;
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
