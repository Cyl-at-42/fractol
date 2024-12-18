# * fractol Makefile *

# Project name
NAME = fractol

# Compiling flags
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = fractol.c \
	complex.c \
	help.c\
	fractol_init.c \
	fractol_calc.c \
	ft.c \
	events.c \
	events_mouse.c \
	events_keys.c \
	palette.c \
	parse_args.c \
	render.c \
	render_exec.c \
	render_coords.c \
	coord_range.c \
	utils.c \
	stock_palettes.c \
	render_loop_functions.c \
	app.c

# Object files
OBJS = $(SRCS:.c=.o)

# mlx
MLX_LIB = libmlx_Linux.a
MLXDIR = minilibx-linux/
MLX = $(MLXDIR)$(MLX_LIB)

# Colors
RED	= "\033[0;31m"
GREEN = "\033[0;32m"
NO_COLOR = "\033[0m"

# Rules
all:$(NAME)

$(NAME):$(OBJS) $(MLX)
	@echo $(GREEN)Making $(NAME)$(NO_COLOR)
	cc $(CFLAGS) -o $(NAME) $(OBJS) -L$(MLXDIR) -lmlx_Linux -lXext -lX11 -lm -lz

%.o:%.c
	@echo $(GREEN)Making object files$(NO_COLOR)
	cc $(CFLAGS) -o $@ -c $<

$(MLX):
	@echo $(GREEN)Making mlx$(NO_COLOR)
	make -C $(MLXDIR)

clean:
	@echo $(RED)Removing .o files$(NO_COLOR)
	rm -rf ${OBJS}
	make clean -C $(MLXDIR)

fclean: clean
	@echo $(RED)Removing $(NAME) $(NO_COLOR)
	rm -rf $(NAME)
	make clean -C $(MLXDIR)

re: fclean all

.PHONY: all clean fclean re bonus