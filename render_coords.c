#include "fractol.h"

void	render_set_coords(t_render *render, t_complex *coords, double zoom)
{
	render->x.start = coords->r - zoom;
	render->x.end = coords->r + zoom;
	render->y.start = coords->i + zoom;
	render->y.end = coords->i - zoom;
	if (render->width > render->height)
		coord_range_adjust_aspect_ratio(&render->x, render->width,
			render->y.end - render->y.start, render->height);
	if (render->height > render->width)
		coord_range_adjust_aspect_ratio(&render->y, render->height,
			render->x.end - render->x.start, render->width);
}

void	render_zoom_to_point(t_render *render, int x, int y, double zoom)
{
	coord_range_zoom_to_point(&render->x, x, render->width, zoom);
	coord_range_zoom_to_point(&render->y, y, render->height, zoom);
}

void	render_begin_move(t_render *render)
{
	render->move.origin_x = render->x.start;
	render->move.origin_y = render->y.start;
	render->move.scale = (render->x.end - render->x.start) / render->width;
}

void	render_update_move(t_render *render, int offset_x, int offset_y)
{
	render->x.start = render->move.origin_x + offset_x * render->move.scale;
	render->x.end = render->x.start + render->move.scale * render->width;
	render->y.start = render->move.origin_y + offset_y * render->move.scale;
	render->y.end = render->y.start - render->move.scale * render->height;
}

void	render_filter_iteration(t_render *render, int iteration_threshold)
{
	float	*points_ptr;
	char	*points_state_ptr;
	char	*points_state_ptr_max;
	float	iteration_thresholdf;

	points_ptr = render->points;
	points_state_ptr = render->points_state;
	points_state_ptr_max = render->points_state
		+ render->width * render->height;
	iteration_thresholdf = iteration_threshold;
	iteration_thresholdf += 1.f;
	while (points_state_ptr < points_state_ptr_max)
	{
		if ((*points_ptr >= iteration_thresholdf) || (*points_ptr == 0.f))
		{
			*points_ptr = 0.f;
			*points_state_ptr = 0;
		}
		else
			*points_state_ptr = 1;
		points_ptr++;
		points_state_ptr++;
	}
}
