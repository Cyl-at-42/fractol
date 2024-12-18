#include "fractol.h"

bool	init_render(t_render *render, int width, int height)
{
	render->points = (float *)malloc(width * height * sizeof(float));
	if (!render->points)
		return (false);
	render->x_coord_table = (double *)malloc(width * sizeof(double));
	if (!render->x_coord_table)
		return (false);
	render->points_state = (char *)malloc(width * height * sizeof(char));
	if (!render->points_state)
		return (false);
	ft_memset((void *)render->points, 0, width * height * sizeof(float));
	ft_memset((void *)render->points_state, 0, width * height * sizeof(char));
	render->points_ptr = render->points;
	render->width = width;
	render->height = height;
	render->set_color = 0x0;
	return (true);
}

void	destroy_render(t_render *render)
{
	free(render->points);
	free(render->x_coord_table);
	free(render->points_state);
}

void	render_set_lod(t_render *render, int lod)
{
	static const unsigned char	patternbitstable[8] = {0x00, 0x01, 0x10, 0x11,
		0x44, 0x55, 0xaa, 0xff};
	static const char			*patterncodes = "6767676740504050"
		"2000300010000000";
	unsigned char				patternbits;
	int							j;
	int							i;

	render->current_lod = lod;
	render->lod.coordmask = (lod >= 1) + ((lod >= 2) << 1) + ((lod >= 3) << 2);
	i = 0;
	while (i < 8)
	{
		patternbits = patternbitstable[patterncodes[i + lod * 8] - '0'];
		j = 0;
		while (j < 8)
		{
			render->lod.renderpattern[i][j] = patternbits & 1;
			patternbits >>= 1;
			j++;
		}
		i++;
	}
}

static void	fast_putpixel(t_img *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

void	render_fill_img_with_points(t_render *render, void *img,
			t_palette *palette)
{
	int		x;
	int		y;
	t_color	clr;
	float	*colorinfo;

	colorinfo = render->points;
	y = 0;
	while (y < render->height)
	{
		x = 0;
		while (x < render->width)
		{
			if (*colorinfo == 0.f)
				clr = render->set_color;
			else
				clr = palette_get_interpolated_color(palette, *colorinfo);
			fast_putpixel(img, x, y, clr);
			colorinfo++;
			x++;
		}
		y++;
	}
}
