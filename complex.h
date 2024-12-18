#ifndef COMPLEX_H
# define COMPLEX_H

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

t_complex	*complex_copy(t_complex *z_dest, t_complex *z_src);
t_complex	*complex_set(t_complex *zr, double real, double imaginary);
t_complex	*complex_add(t_complex *zr, t_complex *z1, t_complex *z2);
t_complex	*complex_fastpow(t_complex *zr, t_complex *z, unsigned int pow);
t_complex	*complex_multiply(t_complex *zr, t_complex *z1, t_complex *z2);

#endif
