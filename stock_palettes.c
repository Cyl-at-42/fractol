#include "fractol.h"

void	init_stock_palettes(t_app *app)
{
	palette_set(&app->stock_palettes[0], 0x000030, 0xffff80);
	palette_add(&app->stock_palettes[0], 0x800000);
	palette_add(&app->stock_palettes[0], 0xff00ff);
	palette_add(&app->stock_palettes[0], 0xffffff);
	palette_add(&app->stock_palettes[0], 0x008000);
	palette_add(&app->stock_palettes[0], 0x00ffff);
	palette_set(&app->stock_palettes[1], 0x000000, 0xff0000);
	palette_add(&app->stock_palettes[1], 0xffffff);
	palette_add(&app->stock_palettes[1], 0xffff00);
	palette_add(&app->stock_palettes[1], 0xff0000);
	palette_set(&app->stock_palettes[2], 0x8000ff, 0xffffff);
	palette_add(&app->stock_palettes[2], 0x00ffff);
	palette_add(&app->stock_palettes[2], 0x000000);
	palette_add(&app->stock_palettes[2], 0x0000ff);
	palette_set(&app->stock_palettes[3], 0xffffff, 0x40c0c0);
	palette_add(&app->stock_palettes[3], 0x000000);
	palette_add(&app->stock_palettes[3], 0xbf6441);
	palette_add(&app->stock_palettes[3], 0xffffff);
	palette_add(&app->stock_palettes[3], 0xd1b02c);
}

void	copy_stock_palette(t_app *app, unsigned int palette_index)
{
	int	i;

	i = app->stock_palettes[palette_index].size;
	app->palette.size = i;
	if (app->palette.offset >= app->palette.size)
		app->palette.offset = 0;
	while (--i >= 0)
		app->palette.colors[i] = app->stock_palettes[palette_index].colors[i];
}
