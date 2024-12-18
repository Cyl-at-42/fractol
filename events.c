#include "fractol.h"

int	event_on_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_loop_end(app->mlx);
	return (0);
}

int	event_on_expose(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app->capture_mouse = false;
	app->request_refresh = true;
	return (0);
}

int	event_on_leave(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app->capture_mouse = false;
	return (0);
}
