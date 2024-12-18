#include "fractol.h"

void	app_cleanexit(t_app *app)
{
	if (app->img.img)
		mlx_destroy_image(app->mlx, app->img.img);
	if (app->window)
		mlx_destroy_window(app->mlx, app->window);
	if (app->mlx)
		mlx_destroy_display(app->mlx);
	destroy_render(&app->render);
	free(app->mlx);
}

void	app_init(t_app *app)
{
	ft_memset((void *)app, 0, sizeof(t_app));
	app->width = 1280;
	app->height = 960;
	app->fractol.start_zoom = 1.5;
	app->fractol.iteration_max = 128;
	app->fractol.power = 2;
	app->fractol.smooth = true;
	init_stock_palettes(app);
	copy_stock_palette(app, 0);
}

static void	app_run_init_first_render(t_app *app)
{
	t_complex	save_coords;

	complex_copy(&save_coords, &app->fractol.start_coords);
	complex_set(&app->fractol.start_coords, -.5, 0.);
	render_set_coords(&app->render, &app->fractol.start_coords, 1.5);
	coord_range_copy(&app->mandelbrot_ref_x, &app->render.x);
	coord_range_copy(&app->mandelbrot_ref_y, &app->render.y);
	complex_copy(&app->fractol.start_coords, &save_coords);
	render_set_coords(&app->render, &app->fractol.start_coords,
		app->fractol.start_zoom);
	app_start_partial_render(app, false);
}

int	app_run_interface(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (app_cleanexit(app), APPRETCODE_MLX);
	app_check_screen_size(app);
	if (!init_render(&app->render, app->width, app->height))
		return (app_cleanexit(app), APPRETCODE_MALLOC);
	app->window = mlx_new_window(app->mlx, app->width, app->height, "Fractol");
	if (!app->window)
		return (app_cleanexit(app), APPRETCODE_WINDOW);
	app->img.img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img.img)
		return (app_cleanexit(app), APPRETCODE_IMG);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
			&app->img.line_length, &app->img.endian);
	mlx_key_hook(app->window, event_on_key, app);
	mlx_hook(app->window, 17, 0, event_on_close, app);
	mlx_expose_hook(app->window, event_on_expose, app);
	mlx_hook(app->window, 6, 1 << 6, event_on_mousemove, app);
	mlx_mouse_hook(app->window, event_on_mouse, app);
	mlx_hook(app->window, 5, 1 << 3, event_on_buttonup, app);
	mlx_hook(app->window, 8, 1 << 5, event_on_leave, app);
	mlx_loop_hook(app->mlx, app_exec_render_loop_function, app);
	app_run_init_first_render(app);
	mlx_loop(app->mlx);
	return (app_cleanexit(app), APPRETCODE_OK);
}

int	main(int argc, char **argv)
{
	static const char	*fractalnames[FTYPECOUNT] = {"mandelbrot", "julia",
		"burningship", "genlambda"};
	static int			(*init_ftns[FTYPECOUNT])(t_fractol *, int, char **)
		= {init_mandelbrot, init_julia, init_burningship, init_genlambda};
	t_app				app;
	int					i;
	int					argindex;

	if (argc == 1)
		return (print_help(), APPRETCODE_OK);
	i = -1;
	while (++i < FTYPECOUNT)
		if (ft_strncmp(fractalnames[i], argv[1], 42) == 0)
			break ;
	if (i == FTYPECOUNT)
		return (print_help(), APPRETCODE_OK);
	app_init(&app);
	argindex = init_ftns[i](&app.fractol, argc, argv);
	if (!argindex)
		return (print_help(), APPRETCODE_ARG);
	if (!parse_args(&app, argindex, argc, argv))
		return (print_help(), APPRETCODE_ARG);
	return (app_run_interface(&app));
}
