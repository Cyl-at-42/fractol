#ifndef COORD_RANGE_H
# define COORD_RANGE_H

typedef struct s_coord_range
{
	double	start;
	double	end;
}	t_coord_range;

void	coord_range_adjust_aspect_ratio(t_coord_range *tgt_coord_range,
			int target_size, double src_range, int src_size);
double	coord_range_lerp(t_coord_range *coord_range, int index, int index_max);
void	coord_range_copy(t_coord_range *dest_range, t_coord_range *src_range);
void	coord_range_zoom_to_point(t_coord_range *coord_range, int point,
			int size, double zoom);

#endif
