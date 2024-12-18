#ifndef PALETTE_H
# define PALETTE_H

typedef unsigned char	t_clrcnl;
typedef unsigned int	t_color;

typedef struct s_palette
{
	t_color	colors[16];
	int		size;
	int		offset;
}	t_palette;

void	palette_set(t_palette *palette, t_color color1, t_color color2);
void	palette_shift(t_palette *palette, int direction);
t_color	palette_get_interpolated_color(t_palette *palette, float index);
void	palette_add(t_palette *palette, t_color color);

#endif
