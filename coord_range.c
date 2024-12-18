#include "fractol.h"

void	coord_range_adjust_aspect_ratio(t_coord_range *tgt_coord_range,
	int target_size, double src_range, int src_size)
{
	double	mid_target_size;
	double	mid_tgt_coord;
	double	half_tgt_range;

	if (src_range < 0.0)
		src_range *= -1.0;
	mid_target_size = (target_size - 1.0) / 2.0;
	mid_tgt_coord = (tgt_coord_range->start + tgt_coord_range->end) / 2.0;
	half_tgt_range = (mid_target_size * src_range) / src_size;
	tgt_coord_range->start = mid_tgt_coord - half_tgt_range;
	tgt_coord_range->end = mid_tgt_coord + half_tgt_range;
}

double	coord_range_lerp(t_coord_range *coord_range, int index, int index_max)
{
	double	i0;
	double	i1;

	i0 = (index_max - index);
	i1 = index;
	i0 /= index_max;
	i1 /= index_max;
	return (i0 * coord_range->start + i1 * coord_range->end);
}

void	coord_range_copy(t_coord_range *dest_range, t_coord_range *src_range)
{
	dest_range->start = src_range->start;
	dest_range->end = src_range->end;
}

void	coord_range_zoom_to_point(t_coord_range *coord_range, int point,
			int size, double zoom)
{
	double	range;
	double	s1;
	double	s2;
	double	p;

	s1 = (size - point - 1.0) / (size - 1.0);
	s2 = point / (size - 1.0);
	p = s1 * coord_range->start + s2 * coord_range->end;
	range = coord_range->end - coord_range->start;
	coord_range->start = p - ((point + 0.0) / size) * (range * zoom);
	coord_range->end = p + ((size - (point + 0.0)) / size) * (range * zoom);
}
