#include "fractol.h"

static void	juliaclick(int x, int y, t_app *app)
{
	if (app->fractol.julia_click)
	{
		if (app->fractol.julia_click_ref)
		{
			app->fractol.p0.r = coord_range_lerp(&app->render.x, x,
					app->render.width);
			app->fractol.p0.i = coord_range_lerp(&app->render.y, y,
					app->render.height);
			app_switch_to_julia(app);
		}
		else
		{
			app->fractol.p0.r = coord_range_lerp(&app->mandelbrot_ref_x, x,
					app->render.width);
			app->fractol.p0.i = coord_range_lerp(&app->mandelbrot_ref_y, y,
					app->render.height);
		}
		app_start_partial_render(app, false);
	}
	if (app->fractol.adjust_s)
	{
		app->fractol.s = (4.0 * x) / app->render.width;
		app_start_partial_render(app, false);
	}
}

int	event_on_mouse(int button, int x, int y, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (button == 3)
		return (juliaclick(x, y, app), 0);
	if (button == 1)
		return (render_begin_move(&app->render), app->capture_mouse = true,
			app->capture_mouse_x = x, app->capture_mouse_y = y, 0);
	if (button == MOUSEWHEEL_DOWN)
		return (render_zoom_to_point(&app->render, x, y, 1.1),
			app_start_partial_render(app, false), 0);
	if (button == MOUSEWHEEL_UP)
		return (render_zoom_to_point(&app->render, x, y, 1.0 / 1.1),
			app_start_partial_render(app, false), 0);
	return (0);
}

int	event_on_mousemove(int x, int y, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->capture_mouse)
	{
		render_update_move(&app->render, app->capture_mouse_x - x,
			y - app->capture_mouse_y);
		app_start_partial_render(app, false);
	}
	return (0);
}

int	event_on_buttonup(int button, int x, int y, void *param)
{
	t_app	*app;

	(void) button;
	(void) x;
	(void) y;
	app = (t_app *)param;
	app->capture_mouse = false;
	return (0);
}
