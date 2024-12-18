#include "fractol.h"

bool	render_is_renderable_lodpt(t_render *render, float *clrindx,
			int x, int y)
{
	if (render->lod.renderpattern[x & 0x7][y & 0x7])
		return (true);
	x &= ~render->lod.coordmask;
	y &= ~render->lod.coordmask;
	*clrindx = *(render->points + y * render->width + x);
	return (false);
}

void	render_begin(t_render *render)
{
	int	i;

	render->finished = false;
	render->current_point_x = 0;
	render->current_point_y = 0;
	render->total_iterations_count = 0;
	render->current_y_coord = render->y.start;
	render->points_ptr = render->points;
	render->points_state_ptr = render->points_state;
	i = 0;
	while (i < render->width)
	{
		render->x_coord_table[i] = coord_range_lerp(&render->x, i,
				render->width - 1);
		i++;
	}
}

void	render_exec_lod(t_render *render, t_fractol *fractol)
{
	int		count;
	float	src_colorindex;

	count = 0;
	while (count < PARTIAL_RENDERING_THRESHOLD)
	{
		if (render_is_renderable_lodpt(render, &src_colorindex,
				render->current_point_x, render->current_point_y))
		{
			*render->points_ptr = fractol->function(
					render->x_coord_table[render->current_point_x],
					render->current_y_coord, fractol);
			count += sel_int(*render->points_ptr == 0.f,
					fractol->iteration_max, *render->points_ptr);
		}
		else
			*render->points_ptr = src_colorindex;
		if (render_advance(render, count))
			return ;
	}
	render->total_iterations_count += count;
}

void	render_exec_lod_addmode(t_render *render, t_fractol *fractol)
{
	int		count;
	float	src_colorindex;

	count = 0;
	while (count < PARTIAL_RENDERING_THRESHOLD)
	{
		if (!*render->points_state_ptr)
		{
			if (render_is_renderable_lodpt(render, &src_colorindex,
					render->current_point_x, render->current_point_y))
			{
				*render->points_ptr = fractol->function(
						render->x_coord_table[render->current_point_x],
						render->current_y_coord, fractol);
				count += sel_int(*render->points_ptr == 0.f,
						fractol->iteration_max, *render->points_ptr);
			}
			else
				*render->points_ptr = src_colorindex;
		}
		if (render_advance(render, count))
			return ;
		render->points_state_ptr++;
	}
	render->total_iterations_count += count;
}

void	render_finish(t_render *render)
{
	char	*points_state_ptr_max;

	render->points_ptr = render->points;
	render->points_state_ptr = render->points_state;
	points_state_ptr_max = render->points_state
		+ render->width * render->height;
	while (render->points_state_ptr < points_state_ptr_max)
		*render->points_state_ptr++ = (*render->points_ptr++ != 0.f);
}
