#include "complex.h"

t_complex	*complex_set(t_complex *zr, double real, double imaginary)
{
	zr->r = real;
	zr->i = imaginary;
	return (zr);
}

t_complex	*complex_copy(t_complex *z_dest, t_complex *z_src)
{
	z_dest->r = z_src->r;
	z_dest->i = z_src->i;
	return (z_dest);
}

t_complex	*complex_add(t_complex *zr, t_complex *z1, t_complex *z2)
{
	zr->r = z1->r + z2->r;
	zr->i = z1->i + z2->i;
	return (zr);
}

t_complex	*complex_fastpow(t_complex *zr, t_complex *z, unsigned int pow)
{
	static const unsigned char	ct23[8] = {0x01, 0x10, 0x02, 0x11,
		0x20, 0x12, 0x21, 0x30};
	int							i;
	double						r;

	zr->r = z->r;
	zr->i = z->i;
	i = ct23[pow - 2] & 3;
	while (--i >= 0)
	{
		r = zr->r * zr->r - zr->i * zr->i;
		zr->i = 2.0 * zr->r * zr->i;
		zr->r = r;
	}
	i = ct23[pow - 2] >> 4;
	while (--i >= 0)
	{
		r = zr->r * (zr->r * zr->r - 3.0 * zr->i * zr->i);
		zr->i = zr->i * (3.0 * zr->r * zr->r - zr->i * zr->i);
		zr->r = r;
	}
	return (zr);
}

t_complex	*complex_multiply(t_complex *zr, t_complex *z1, t_complex *z2)
{
	double	r;

	r = z1->r * z2->r - z1->i * z2->i;
	zr->i = z1->i * z2->r + z1->r * z2->i;
	zr->r = r;
	return (zr);
}
