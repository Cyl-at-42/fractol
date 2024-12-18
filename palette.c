#include "fractol.h"

static unsigned char	blend_channel(float value1, float value2, float blend)
{
	return ((unsigned char)((1. - blend) * value1 + blend * value2));
}

t_color	palette_get_interpolated_color(t_palette *palette, float index)
{
	int		i;
	int		s;
	float	s2;
	t_color	color1;
	t_color	color2;

	if (index < 0.f)
		index = 0.0;
	index += palette->offset * 16.f;
	i = index / 16.f;
	s = index;
	s2 = index - i * 16.f;
	s %= 16;
	i %= palette->size;
	color1 = palette->colors[i++];
	if (i == palette->size)
		i = 0;
	color2 = palette->colors[i];
	return ((blend_channel((t_clrcnl)color1, (t_clrcnl)color2, s2 / 16.f))
		| ((blend_channel((t_clrcnl)(color1 >> 8),
				(t_clrcnl)(color2 >> 8), s2 / 16.f)) << 8)
		| ((blend_channel((t_clrcnl)(color1 >> 16),
				(t_clrcnl)(color2 >> 16), s2 / 16.f)) << 16));
}

void	palette_set(t_palette *palette, t_color color1, t_color color2)
{
	palette->colors[0] = color1;
	palette->colors[1] = color2;
	palette->size = 2;
	palette->offset = 0;
}

void	palette_shift(t_palette *palette, int direction)
{
	palette->offset += direction;
	if (palette->offset < 0)
		palette->offset = palette->size - 1;
	if (palette->offset >= palette->size)
		palette->offset = 0;
}

void	palette_add(t_palette *palette, t_color color)
{
	if (palette->size >= 16)
		return ;
	palette->colors[palette->size] = color;
	palette->size++;
	palette->colors[palette->size] = palette->colors[0];
}
