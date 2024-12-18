#include "fractol.h"

int	clamp_int(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

double	sel_double(bool condition, double val_true, double val_false)
{
	if (condition)
		return (val_true);
	return (val_false);
}

int	sel_int(bool condition, int val_true, int val_false)
{
	if (condition)
		return (val_true);
	return (val_false);
}

char	*parse_int(int *out_int, bool *out_valid, char *str)
{
	unsigned int	nbr;
	char			*in_str;
	char			*msd_str;

	nbr = 0;
	in_str = str;
	str += (*str == '-' || *str == '+');
	*out_valid = (*str == '0');
	while (*str == '0')
		str++;
	if ((*str < '0' || *str > '9') && !*out_valid)
		return (in_str);
	msd_str = str;
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*str++ - '0');
	if (((str - msd_str) > 10) || ((str - msd_str) == 10 && *msd_str >= '4'))
		return (*out_valid = 0, str);
	if ((nbr == 0x80000000) && (*in_str == '-'))
		return (*out_int = 0x80000000, *out_valid = 1, str);
	*out_valid = (nbr < 0x80000000);
	return (*out_int = (int)nbr * (1 - ((*in_str == '-') << 1)), str);
}

char	*parse_double(double *out_double, bool *out_valid, char *str)
{
	double	nbr;
	double	mult;
	char	*in_str;

	nbr = 0.;
	in_str = str;
	str += (*str == '-' || *str == '+');
	*out_valid = ((*str >= '0') && (*str <= '9'));
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10. + (*str++ - '0');
	if (*str != '.' && !*out_valid)
		return (in_str);
	if (*str != '.')
		return (*out_double = nbr * (1. - 2. * (*in_str == '-')), str);
	str++;
	if (!*out_valid && ((*str < '0') || (*str > '9')))
		return (in_str);
	mult = 1.;
	while (*str >= '0' && *str <= '9')
	{
		mult /= 10.;
		nbr = nbr + mult * (*str++ - '0');
	}
	*out_double = nbr * (1. - 2. * (*in_str == '-'));
	return (*out_valid = true, str);
}
