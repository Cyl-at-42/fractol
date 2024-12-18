#include "fractol.h"

int	init_mandelbrot(t_fractol *fractol, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	fractol->function = fractol_lib_mandelbrot;
	complex_set(&fractol->start_coords, -.5, 0.);
	fractol->julia_click_ref = true;
	fractol->julia_click = true;
	return (2);
}

int	init_julia(t_fractol *fractol, int argc, char**argv)
{
	char	*str_ptr;
	bool	valid;

	fractol->function = fractol_lib_julia;
	fractol->julia_click = true;
	if (argc <= 3)
		return (0);
	str_ptr = parse_double(&fractol->p0.r, &valid, argv[2]);
	if (*str_ptr)
		return (0);
	str_ptr = parse_double(&fractol->p0.i, &valid, argv[3]);
	if (*str_ptr)
		return (0);
	return (4);
}

int	init_burningship(t_fractol *fractol, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	fractol->function = fractol_lib_burningship;
	complex_set(&fractol->start_coords, -0.5, 0.5);
	return (2);
}

int	init_genlambda(t_fractol *fractol, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	fractol->function = fractol_lib_genlambda;
	fractol->start_zoom = 2.5;
	fractol->s = 2.0;
	fractol->adjust_s = true;
	return (2);
}
