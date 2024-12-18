#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>
# include "ft.h"
# include "complex.h"
# include "coord_range.h"
# include "palette.h"
# include "minilibx-linux/mlx.h"

# define APPRETCODE_OK 0
# define APPRETCODE_ARG 1
# define APPRETCODE_MALLOC 2
# define APPRETCODE_MLX 3
# define APPRETCODE_WINDOW 4
# define APPRETCODE_IMG 5

# define FTYPECOUNT 4

# define ITERATIONMIN 16
# define ITERATIONMAXMAX 512
# define PARTIAL_RENDERING_THRESHOLD 1400000

# define MOUSEWHEEL_DOWN 5
# define MOUSEWHEEL_UP 4

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_fractol
{
	float		(*function)(double, double, struct s_fractol *);
	int			iteration_max;
	int			power;
	t_complex	p0;
	t_complex	start_coords;
	double		start_zoom;
	double		d0;
	double		d1;
	double		escape_module;
	double		s;
	bool		smooth;
	bool		julia_click_ref;
	bool		julia_click;
	bool		adjust_s;
}				t_fractol;

typedef struct s_lod
{
	int				coordmask;
	unsigned char	renderpattern[8][8];
}	t_lod;

typedef struct s_coord_move
{
	double	origin_x;
	double	origin_y;
	double	scale;
}	t_coord_move;

typedef struct s_render
{
	t_color			set_color;
	t_lod			lod;
	t_coord_range	x;
	t_coord_range	y;
	t_coord_move	move;
	long			total_iterations_count;
	int				width;
	int				height;
	float			*points;
	float			*points_ptr;
	char			*points_state;
	char			*points_state_ptr;
	double			*x_coord_table;
	double			current_y_coord;
	int				current_point_x;
	int				current_point_y;
	int				current_lod;
	bool			finished;
	bool			addmode;
}	t_render;

typedef struct s_app
{
	t_fractol		fractol;
	t_img			img;
	t_render		render;
	t_palette		palette;
	t_palette		stock_palettes[4];
	t_coord_range	mandelbrot_ref_x;
	t_coord_range	mandelbrot_ref_y;
	int				width;
	int				height;
	void			*(*render_function)(struct s_app *);
	void			*mlx;
	void			*window;
	int				capture_mouse_x;
	int				capture_mouse_y;
	bool			capture_mouse;
	bool			request_refresh;
	bool			arg_p_here;
	bool			arg_s_here;
}	t_app;

char	*parse_int(int *out_int, bool *out_valid, char *str);
char	*parse_double(double *out_double, bool *out_valid, char *str);
int		clamp_int(int val, int min, int max);
double	sel_double(bool condition, double val_true, double val_false);
int		sel_int(bool condition, int val_true, int val_false);
int		init_mandelbrot(t_fractol *fractol, int argc, char**argv);
int		init_julia(t_fractol *fractol, int argc, char**argv);
int		init_burningship(t_fractol *fractol, int argc, char**argv);
int		init_genlambda(t_fractol *fractol, int argc, char**argv);
float	fractol_lib_mandelbrot(double x, double y, t_fractol *fractol);
float	fractol_lib_julia(double x, double y, t_fractol *fractol);
float	fractol_lib_burningship(double x, double y, t_fractol *fractol);
float	fractol_lib_genlambda(double x, double y, t_fractol *fractol);
void	print_help(void);
int		event_on_close(void *param);
int		event_on_expose(void *param);
int		event_on_key(int keycode, void *param);
int		event_on_leave(void *param);
int		event_on_buttonup(int button, int x, int y, void *param);
int		event_on_mouse(int button, int x, int y, void *param);
int		event_on_mousemove(int x, int y, void *param);
int		parse_arg_p(t_app *app, int argindex, int argc, char**argv);
int		parse_arg_s(t_app *app, int argindex, int argc, char**argv);
void	*parse_args_get_function(char *argstr);
bool	parse_args(t_app *app, int argindex, int argc, char **argv);
bool	init_render(t_render *render, int width, int height);
void	destroy_render(t_render *render);
void	render_set_lod(t_render *render, int lod);
void	render_begin(t_render *render);
void	render_fill_img_with_points(t_render *render, void *img,
			t_palette *palette);
void	render_zoom_to_point(t_render *render, int x, int y, double zoom);
void	render_begin_move(t_render *render);
void	render_update_move(t_render *render, int offset_x, int offset_y);
void	render_set_coords(t_render *render, t_complex *coords, double zoom);
void	render_finish(t_render *render);
void	render_filter_iteration(t_render *render, int iteration_threshold);
void	render_exec_lod(t_render *render, t_fractol *fractol);
void	render_exec_lod_addmode(t_render *render, t_fractol *fractol);
bool	render_advance(t_render *render, int count);
void	*rlf_init_render(t_app *app);
void	*rlf_init_render_addmode(t_app *app);
void	app_start_partial_render(t_app *app, bool addmode);
void	app_reset_to_mandelbrot(t_app *app);
void	app_switch_to_julia(t_app *app);
int		app_exec_render_loop_function(void *param);
void	app_check_screen_size(t_app *app);
void	init_stock_palettes(t_app *app);
void	copy_stock_palette(t_app *app, unsigned int palette_index);

#endif
