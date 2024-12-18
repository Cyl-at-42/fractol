#include "fractol.h"

void	print_help(void)
{
	static const char	helptext[] = {"usage:\n------\n"
		"fractol fractaltype typeopts [-p power (2-9)] [-s width height]\n\n"
		"types available:\n"
		"fractol mandelbrot\nfractol julia coord-real coord-imaginary\n"
		"fractol burningship\nfractol genlambda\n\n"
		"Mouse:\n"
		"Wheel up\tZoom in\n"
		"Wheel down\tZoom out\n"
		"Left button\tMove image with mouse\n"
		"Right button\t(Mandelbrot) Switch to Julia point\n"
		"\t\t(Julia) Set origin point\n"
		"\t\t(genlambda) Adjust shape factor, (0. to 4. along r axis)\n\n"
		"Keys:\n"
		"Arrows\t\tScroll image\n"
		"F1-4\t\tChange palette\n"
		"Home\t\tReset coordinates & zoom\n"
		"p\t\tIncrease iteration count\n"
		"o\t\tDecrease iteration count\n"
		"s\t\tToggle smoothing\n"
		"w\t\tshift palette up\n"
		"a\t\tshift palette down\n"
		"m\t\t(Julia) Switch to Mandelbrot\n\n\0"
	};

	write(1, helptext, ft_strlen(helptext));
}
