#include "fractol.h"

void	app_reset_to_mandelbrot(t_app *app)
{
	app->fractol.function = fractol_lib_mandelbrot;
	app->fractol.start_zoom = 1.5;
	app->fractol.julia_click = true;
	app->fractol.julia_click_ref = true;
	complex_set(&app->fractol.start_coords, -.5, 0.);
	coord_range_copy(&app->render.x, &app->mandelbrot_ref_x);
	coord_range_copy(&app->render.y, &app->mandelbrot_ref_y);
}

void	app_switch_to_julia(t_app *app)
{
	coord_range_copy(&app->mandelbrot_ref_x, &app->render.x);
	coord_range_copy(&app->mandelbrot_ref_y, &app->render.y);
	app->fractol.function = fractol_lib_julia;
	app->fractol.julia_click = true;
	app->fractol.julia_click_ref = false;
	complex_set(&app->fractol.start_coords, 0., 0.);
	render_set_coords(&app->render, &app->fractol.start_coords, 1.5);
}

void	app_check_screen_size(t_app *app)
{
	int	x_screen_size;
	int	y_screen_size;

	mlx_get_screen_size(app->mlx, &x_screen_size, &y_screen_size);
	app->width = clamp_int(app->width, 640, x_screen_size);
	app->height = clamp_int(app->height, 480, y_screen_size);
}

void	app_start_partial_render(t_app *app, bool addmode)
{
	if (addmode)
		app->render_function = rlf_init_render_addmode;
	else
		app->render_function = rlf_init_render;
}

int	app_exec_render_loop_function(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->render_function)
		app->render_function = app->render_function(app);
	if (app->request_refresh)
	{
		render_fill_img_with_points(&app->render, &app->img.img, &app->palette);
		mlx_put_image_to_window(app->mlx, app->window, app->img.img, 0, 0);
		app->request_refresh = false;
	}
	return (0);
}
