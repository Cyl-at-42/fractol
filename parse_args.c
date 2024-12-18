#include "fractol.h"

int	parse_arg_p(t_app *app, int argindex, int argc, char **argv)
{
	char	pwrc;

	if (app->arg_p_here)
		return (0);
	if (argindex >= argc)
		return (0);
	pwrc = *argv[argindex];
	if ((pwrc < '2') || (pwrc > '9'))
		return (0);
	app->fractol.power = pwrc - '0';
	if (argv[argindex][1])
		return (0);
	argindex++;
	app->arg_p_here = true;
	return (argindex);
}

int	parse_arg_s(t_app *app, int argindex, int argc, char**argv)
{
	char	*endptr;
	bool	isvalid;

	if (app->arg_s_here)
		return (0);
	endptr = parse_int(&app->width, &isvalid, argv[argindex]);
	if (!isvalid || *endptr)
		return (0);
	if (app->width <= 0)
		return (0);
	if (++argindex == argc)
		return (0);
	endptr = parse_int(&app->height, &isvalid, argv[argindex]);
	if (!isvalid || *endptr)
		return (0);
	if (app->height <= 0)
		return (0);
	argindex++;
	app->arg_s_here = true;
	return (argindex);
}

void	*parse_args_get_function(char *argstr)
{
	if (argstr[0] != '-')
		return (NULL);
	if (argstr[1] == 's')
		if (!argstr[2])
			return (parse_arg_s);
	if (argstr[1] == 'p')
		if (!argstr[2])
			return (parse_arg_p);
	return (NULL);
}

bool	parse_args(t_app *app, int argindex, int argc, char **argv)
{
	int	(*fp)(t_app *, int, int, char **);

	while (argindex < argc)
	{
		fp = parse_args_get_function(argv[argindex]);
		if (!fp)
			return (false);
		argindex = fp(app, ++argindex, argc, argv);
		if (!argindex)
			return (false);
	}
	return (true);
}
