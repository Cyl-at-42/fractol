#include "fractol.h"

static void	*rlf_exec_render(t_app *app)
{
	render_exec_lod(&app->render, &app->fractol);
	app->request_refresh = true;
	if (app->render.finished)
	{
		if (app->render.current_lod)
		{
			render_set_lod(&app->render, --app->render.current_lod);
			render_begin(&app->render);
			return (rlf_exec_render);
		}
		render_finish(&app->render);
		return (NULL);
	}
	return (rlf_exec_render);
}

static void	*rlf_exec_render_addmode(t_app *app)
{
	render_exec_lod_addmode(&app->render, &app->fractol);
	app->request_refresh = true;
	if (app->render.finished)
	{
		if (app->render.current_lod)
		{
			render_set_lod(&app->render, --app->render.current_lod);
			render_begin(&app->render);
			return (rlf_exec_render_addmode);
		}
		render_finish(&app->render);
		return (NULL);
	}
	return (rlf_exec_render_addmode);
}

void	*rlf_init_render(t_app *app)
{
	app->render.addmode = false;
	render_set_lod(&app->render, 3);
	render_begin(&app->render);
	return (rlf_exec_render);
}

void	*rlf_init_render_addmode(t_app *app)
{
	app->render.addmode = true;
	render_set_lod(&app->render, 3);
	render_begin(&app->render);
	return (rlf_exec_render_addmode(app));
}

bool	render_advance(t_render *render, int count)
{
	render->current_point_x++;
	if (render->current_point_x == render->width)
	{
		render->current_point_x = 0;
		render->current_point_y++;
		render->current_y_coord = coord_range_lerp(&render->y,
				render->current_point_y, render->height - 1);
	}
	if (render->current_point_y == render->height)
	{
		render->finished = true;
		render->total_iterations_count += count;
		return (true);
	}
	render->points_ptr++;
	return (false);
}
