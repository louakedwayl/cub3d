

#ifndef CUB3D_H
# define CUB3D_H


# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WINDOW_WIDTH 700
# define WINDOW_HEIGHT 700

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# define DEBUG 1

// utils
typedef enum e_response
{
	NOTHING,
	NEED_TO_BREAK,
	NEED_TO_CONTINUE,
	NEED_TO_RETURN_TRUE,
	NEED_TO_RETURN_FALSE
}	t_response;

typedef struct s_2dpoint
{
	int	x;
	int	y;
}	t_2dpoint;

// mlx data
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
}	t_mlx_data;

typedef struct s_put_pixel_data
{
	int		b_pixel;
	int		size_line;
	int		endian;
	int		pixel_pos;
	int		color;
}	t_put_pixel_data;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_parsing_data
{
	int			fd;
	char		**map;
	char		*north;
	char		*west;
	char		*south;
	char		*east;
	void		*mlx;
	void		*mlx_win;
	int			floor[3];
	int			ceiling[3];
	t_img		img_north;
	t_img		img_west;
	t_img		img_south;
	t_img		img_east;
}				t_parsing_data;

typedef struct s_data
{
	t_mlx_data	*mlx_data;
	char		**map;
	t_2dpoint	player_pos;
	int			map_width;
	int			map_height;
	int			FOV;
	int			player_look_direction;
}	t_data;

//. CORE - - - - - - - - - - - - - - - - - - - - - - - - -

// main.c

// start_game.c
void	start_game(t_parsing_data *data);

//. FOLDER - - - - - - - - - parsing - - - - - - - - - - -

// check_args.c
int				check_nbr_arg(int argc);
int 			check_name_map(char **argv);
int				open_map(t_parsing_data *data, char *map);

//. FOLDER - - - - - - - - - ray_casting - - - - - - - - -

// debug.c

// draw_simple.c
void			put_pixel_on_image(void *img, int x, int y, int color);
void			draw_line(t_data *data, t_2dpoint a, t_2dpoint b, int color);
void			draw_white_square(t_data *data, t_2dpoint top_left, t_2dpoint top_right, t_2dpoint bot_left, t_2dpoint bot_right);
void			draw_square_around_playerpos(t_data *data);

// free.c
void			free_all_and_exit(t_data *data, int exitcode, char *optional_msg);

// hook.c
int				esc_destroy_all(t_data *data);
int				key_hook(int keycode, t_data *data);

// init.c
t_mlx_data		*init_mlx_data(t_data *data);

// raycast.c
void			raycast(t_data *data);

// utils.c
t_2dpoint		make_point(int x_value, int y_value);

#endif
