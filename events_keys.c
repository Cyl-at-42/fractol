#include "fractol.h"

static int	event_on_key_1(int keycode, t_app *app)
{
	if (keycode == XK_F1)
		return (copy_stock_palette(app, 0), app->request_refresh = true, 1);
	if (keycode == XK_F2)
		return (copy_stock_palette(app, 1), app->request_refresh = true, 1);
	if (keycode == XK_F3)
		return (copy_stock_palette(app, 2), app->request_refresh = true, 1);
	if (keycode == XK_F4)
		return (copy_stock_palette(app, 3), app->request_refresh = true, 1);
	if (keycode == 109)
		if (app->fractol.julia_click && !app->fractol.julia_click_ref)
			return (app_reset_to_mandelbrot(app),
				app_start_partial_render(app, false), 1);
	if (keycode == XK_Escape)
		return (mlx_loop_end(app->mlx), 1);
	if (keycode == 115)
		return (app->fractol.smooth = 1 - app->fractol.smooth,
			app_start_partial_render(app, false), 1);
	if (keycode == 113)
		return (palette_shift(&app->palette, 1),
			app->request_refresh = true, 1);
	if (keycode == 119)
		return (palette_shift(&app->palette, -1),
			app->request_refresh = true, 1);
	return (0);
}

static int	event_on_key_2(int keycode, t_app *app)
{
	if (keycode == XK_Down)
		return (render_begin_move(&app->render),
			render_update_move(&app->render, 0, -64),
			app_start_partial_render(app, false), 1);
	if (keycode == XK_Up)
		return (render_begin_move(&app->render),
			render_update_move(&app->render, 0, 64),
			app_start_partial_render(app, false), 1);
	if (keycode == XK_Left)
		return (render_begin_move(&app->render),
			render_update_move(&app->render, -64, 0),
			app_start_partial_render(app, false), 1);
	if (keycode == XK_Right)
		return (render_begin_move(&app->render),
			render_update_move(&app->render, 64, 0),
			app_start_partial_render(app, false), 1);
	if (keycode == XK_Home)
		return (render_set_coords(&app->render,
				&app->fractol.start_coords, app->fractol.start_zoom),
			app_start_partial_render(app, false), 1);
	return (0);
}

static int	event_on_key_3(int keycode, t_app *app)
{
	if (keycode == 111)
	{
		app->fractol.iteration_max -= 16;
		if (app->fractol.iteration_max < ITERATIONMIN)
			app->fractol.iteration_max = ITERATIONMIN;
		return (render_filter_iteration(&app->render,
				app->fractol.iteration_max), app->request_refresh = true, 1);
	}
	return (0);
}

int	event_on_key(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (event_on_key_1(keycode, app))
		return (0);
	if (event_on_key_2(keycode, app))
		return (0);
	if (event_on_key_3(keycode, app))
		return (0);
	if ((keycode == 112) && (app->fractol.iteration_max != ITERATIONMAXMAX))
	{
		app->fractol.iteration_max += 16;
		if (app->fractol.iteration_max > ITERATIONMAXMAX)
		{
			app->fractol.iteration_max = ITERATIONMAXMAX;
			render_filter_iteration(&app->render, 99999);
		}
		if (!app->render.finished)
			app_start_partial_render(app, app->render.addmode);
		else
			app_start_partial_render(app, true);
	}
	return (0);
}
