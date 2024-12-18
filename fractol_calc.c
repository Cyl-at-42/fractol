#include "fractol.h"

float	fractol_lib_mandelbrot(double x, double y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	zc;
	int			iteration;
	double		sq_module;

	fractol->escape_module = sel_double(fractol->smooth, 20., 4.);
	complex_set(&z, 0., 0.);
	complex_set(&zc, x, y);
	fractol->d0 = log(fractol->power);
	iteration = 0;
	while (iteration++ < fractol->iteration_max)
	{
		complex_add(&z, complex_fastpow(&z, &z, fractol->power), &zc);
		sq_module = z.r * z.r + z.i * z.i;
		if (sq_module >= fractol->escape_module)
		{
			if (!fractol->smooth)
				return (iteration);
			return (iteration + 1.f - log(log(sqrt(sq_module))) / fractol->d0);
		}
	}
	return (0.f);
}

float	fractol_lib_julia(double x, double y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	zc;
	int			iteration;
	double		sq_module;

	fractol->escape_module = sel_double(fractol->smooth, 20., 4.);
	complex_copy(&zc, &fractol->p0);
	complex_set(&z, x, y);
	fractol->d0 = log(fractol->power);
	iteration = 0;
	while (iteration++ < fractol->iteration_max)
	{
		complex_add(&z, complex_fastpow(&z, &z, fractol->power), &zc);
		sq_module = z.r * z.r + z.i * z.i;
		if (sq_module >= fractol->escape_module)
		{
			if (!fractol->smooth)
				return (iteration);
			sq_module = sqrt(sq_module);
			return (iteration + 1.f - log(log(sq_module)) / fractol->d0);
		}
	}
	return (0.f);
}

static t_complex	*complex_square_abs(t_complex *zr, t_complex *z)
{
	double	r;

	if (z->r < 0)
		z->r = -z->r;
	if (z->i < 0)
		z->i = -z->i;
	r = z->r * z->r - z->i * z->i;
	zr->i = -2.0 * z->r * z->i;
	zr->r = r;
	return (zr);
}

float	fractol_lib_burningship(double x, double y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	zc;
	int			iteration;
	double		sq_module;

	fractol->escape_module = sel_double(fractol->smooth, 20., 4.);
	complex_set(&z, 0., 0.);
	complex_set(&zc, x, y);
	iteration = 0;
	while (iteration++ < fractol->iteration_max)
	{
		complex_add(&z, complex_square_abs(&z, &z), &zc);
		sq_module = z.r * z.r + z.i * z.i;
		if (sq_module >= fractol->escape_module)
		{
			if (!fractol->smooth)
				return (iteration);
			sq_module = sqrt(sq_module);
			return (iteration + 1.f - log(log(sq_module)) / log(2.));
		}
	}
	return (0.f);
}

float	fractol_lib_genlambda(double x, double y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	zc;
	t_complex	z0;
	int			iteration;
	double		sq_module;

	fractol->d1 = 1.0 + (fractol->s - 1.0) * (1 << 0);
	complex_set(&z, .5, 0.);
	complex_set(&zc, x, y);
	fractol->d0 = log2(fractol->power + 0.25 * fractol->power);
	iteration = 0;
	while (iteration++ < fractol->iteration_max)
	{
		complex_fastpow(&z0, &z, fractol->power);
		complex_set(&z0, 1.0 - fractol->d1 * z0.r, -fractol->d1 * z0.i);
		complex_multiply(&z, &zc, complex_multiply(&z0, &z0, &z));
		sq_module = z.r * z.r + z.i * z.i;
		if (sq_module >= sel_double(fractol->smooth, 256., 4.))
			return (sel_double(fractol->smooth, iteration
					+ log(log(256.0) / log(sqrt(sq_module))) / fractol->d0,
					iteration));
	}
	return (0.f);
}
