

#ifndef CUB3D_H
# define CUB3D_H


# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <X11/Xlib.h>

# define AZERTY 0
# define QWERTY 1
# define KEYBOARD_TYPE QWERTY

# define WINDOW_WIDTH 700
# define WINDOW_HEIGHT 700

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# define Z_KEY 122
# define Q_KEY 113
# define S_KEY 115
# define D_KEY 100

# define W_KEY 119
# define A_KEY 97

# define TOP_ARROW 65362
# define BOTTOM_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define ECHAP_KEY 65307
# define TOP_RIGHT_CROSS 17

# define KEY_NUMPAD0 65438
# define KEY_TAB 65289

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef M_PI_2
#  define M_PI_2 1.5707963267948966
# endif

// # define SQUARE_SIZE 88

// colors
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define CYAN 0x00ffff
# define MAGENTA 0xff00ff
# define YELLOW 0xffff00
# define ORANGE 0xffa500
# define PURPLE 0x800080
# define PINK 0xffc0cb
# define BROWN 0x8b4513
# define WHITE 0xffffff
# define BLACK 0x000000
# define GRAY 0x808080
# define LIGHT_GRAY 0xd3d3d3
# define DARK_GRAY 0x404040
# define GOLD 0xffd700
# define SILVER 0xc0c0c0
# define NAVY 0x000080
# define TEAL 0x008080
# define LIME 0x32cd32

// utils
typedef enum e_response
{
	NOTHING,
	NEED_TO_BREAK,
	NEED_TO_CONTINUE,
	NEED_TO_RETURN_TRUE,
	NEED_TO_RETURN_FALSE
}	t_response;

typedef enum e_orientation
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_orientation;

typedef struct s_2dpoint
{
	int	x;
	int	y;
}	t_2dpoint;

typedef struct s_2dpoint_float
{
	float	x;
	float	y;
}	t_2dpoint_float;

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
	int		width;
	int		height;
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
	int			floor_color;
	int			ceil_color;
	t_img		img_north;
	t_img		img_west;
	t_img		img_south;
	t_img		img_east;
}				t_parsing_data;

typedef struct s_column_draw_data
{
	int screen_height;
	float view_distance;
	float column_height;
	int top;
	int bottom;
	t_2dpoint a;
	t_2dpoint b; // plus grande valeur car en bas
	t_2dpoint ceilling;
	t_2dpoint floor;
	int color;
}	t_column_draw_data;

typedef struct s_square_data
{
	t_2dpoint	top_left;
	t_2dpoint	top_right;
	t_2dpoint	bot_left;
	t_2dpoint	bot_right;
}	t_square_data;

typedef struct s_raycast_data
{
	int debug_print_limit;

	t_2dpoint_float	ray;
	t_2dpoint_float	hit_point;
	t_2dpoint_float	on_map_float;
	t_2dpoint		on_map;

	float x;
	float y;

	int render_distance;
	int i;

	int last_orientation;
	int print_limit_count;
}	t_raycast_data;

typedef struct s_draw_data
{
	float			normalized_hit_part;
	t_img			texture;
	int				texture_x;
	int				line_height;
	int				y;
	int				color;
	int				diff;
	int				texture_y;
	int				high;
}	t_draw_data;

typedef struct s_line_data
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line_data;

typedef struct s_ray_data
{
	float			hit_part_side;
	float			hit_part_vertical;
	float			temp_map_coord;
	t_2dpoint_float	point_x_projection;
	t_2dpoint_float	point_y_projection;
	t_2dpoint_float	on_map_cpy;
	t_2dpoint		temp;
	t_2dpoint_float	on_map;
	float			angle_rad;
	float			dx;
	float			dy;
	float			distance;
}	t_ray_data;

typedef struct s_data
{
	t_mlx_data			*mlx_data;
	char				**map;
	t_2dpoint			player_pos;
	int					map_width;
	int					map_height;
	int					FOV;
	int					player_look_angle;
	int					player_vertical_look;
	int					debug_color;
	int					last_x;
	int					last_y;

	t_orientation		wall_orientation;
	float				hit_part;

	t_bool				mode_mini;
	int					mini_scale;
	int					mini_offset;
	t_bool				key_hook_active;
	t_bool				debug_mode;

	float				square_size;

	t_raycast_data		rc;
	t_column_draw_data	draw_data;

	float				delta_x;
	float				delta_y;
	float				side_delta_x;
	float				side_delta_y;



	t_parsing_data		*parsing_data;
}	t_data;

//. CORE - - - - - - - - - - - - - - - - - - - - - - - - -

// main.c

// start_game.c
void			minimise_point(t_data *data, t_2dpoint *point);
void			minimise_point_float(t_data *data, t_2dpoint_float *point);
void			convert_map_coords_to_window_coords(t_data *data, t_2dpoint *point);
void 			convert_window_coords_to_map_coords(t_data *data, t_2dpoint *point);
void			convert_map_coords_to_window_coords_float(t_data *data, t_2dpoint_float *point);
void			 convert_window_coords_to_map_coords_float(t_data *data, t_2dpoint_float *point);
t_2dpoint		point_float_to_int(t_2dpoint_float point);
void			start_game(t_parsing_data *data);

//. FOLDER - - - - - - - - - parsing - - - - - - - - - - -

//' blue.c
char			*ft_blue(char *line);
int				set_blue(char **line);

// check_args.c
int				check_nbr_arg(int argc);
int				check_name_map(char **argv);
int				open_map(t_parsing_data *data, char *map);
int				handler_open_map(int argc, char **argv, t_parsing_data *data);

//' green.c
char			*ft_green(char *line);
int				set_green(char **line);

// parse_utils.c
void			ft_free(char **str);
void			init_data(t_parsing_data *data);
void			free_data(t_parsing_data *data);
int				is_digit_string(char *string);

// parse.c
int				ft_create_image(t_parsing_data *data);
int				parse(int argc, char **argv, t_parsing_data *data);

//' red.c
char			*ft_red(char *line);
int				set_red(char **line);

// set_data.c
int				set_map(t_parsing_data *data);
int				set_data(t_parsing_data *data);
int				set_var(t_parsing_data *data);

// set_ea.c
int				set_ea(t_parsing_data *data, char **line);

// set_no.c
int				set_no(t_parsing_data *data, char **line);

// set_so.c
int				set_so(t_parsing_data *data, char **line);

// set_var_select.c
int				set_var_select(t_parsing_data *data, char *line);
int				set_var_select2(t_parsing_data *data, char *line);
int				set_floor(t_parsing_data *data, char **line);
int				set_ceiling(t_parsing_data *data, char **line);

// set_we.c
int				set_we(t_parsing_data *data, char **line);

//. FOLDER - - - - - - - - - ray_casting - - - - - - - - -

// debug.c
void			print_point(t_2dpoint point);
void			print_point_float(t_2dpoint_float point);
void			print_map(char **map);
void			toggle_debug_mode(t_data *data);

// draw_simple.c
void			put_pixel_on_image(void *img, int x, int y, int color);
void			draw_line(t_data *data, t_2dpoint a, t_2dpoint b, int color);
void			draw_white_square(t_data *data, t_square_data *sd);
void			draw_square_around_playerpos(t_data *data);
void			draw_square_around_point(t_data *data, t_2dpoint point);

void			draw_debug_square(t_data *data, t_2dpoint_float point, int size);

// draw_column.c
void			draw_pixel_column(t_data *data, int column, float distance);

// free.c
int				esc_destroy_all(t_data *data);
void			clear_map(char **map);
void			free_all_and_exit(t_data *data, int exitcode, char *optional_msg);

// hook.c
int				int_trunc(int value, int min, int max);
int				key_hook(int keycode, t_data *data);
int				mouse_move_hook(int x, int y, t_data *data);
t_bool			player_is_in_wall(t_data *data);
void			look_vertical(t_data *data, int y);

// init.c
t_mlx_data		*init_mlx_data(t_data *data);

// raycast.c
void			forward_ray(t_data *data, t_2dpoint_float *ray, float angle);
void			update_window(t_data *data);
void			draw_map(t_data *data);
float			process_raycasting(t_data *data, float cast_angle);
void			raycast(t_data *data);

// map_init.c
char			*ft_allocplus(char *buffer, size_t size);
int				get_longest_line(char **map);
int				get_map_height(char **map);
void			fill_newmap(t_data *data, int i, int max, char **newmap);
t_bool			transform_to_square_and_cover(t_data *data);

// look.c
void			look_up(t_data *data, int sensi, int diff_y);
void			look_down(t_data *data, int sensi, int diff_y);
void			look_right(t_data *data, int sensi, int diff_x);
void			look_left(t_data *data, int sensi, int diff_x);
void			look_horizontal(t_data *data, int x);

// move.c
int				mouse_move_hook(int x, int y, t_data *data);
void			move_azerty(t_data *data, int keycode);
void			move_qwerty(t_data *data, int keycode);
void			init_movement_vars(t_data *data);
void			move_player(t_data *data, int keycode);

// utils.c
t_2dpoint		make_point(int x_value, int y_value);
t_2dpoint_float	make_float_point(float x_value, float y_value);
float			get_distance(t_2dpoint a, t_2dpoint b);
float			get_distance_float(t_2dpoint_float a, t_2dpoint_float b);

// ray.c
void			update_ray(t_data *data, float cast_angle);
void			init_raycast_vars(t_data *data);

void			init_raydata(t_data *data, float angle, t_ray_data *rd, t_2dpoint_float *ray);
void			project_ray_horizontal(t_data *data, t_2dpoint_float *ray, t_ray_data *rd);
void			project_ray_vertical(t_data *data, t_2dpoint_float *ray, t_ray_data *rd);
int				is_near_corner(float x, float y, float square_size);

float			float_trunc(float value, float min, float max);

//parse_utils2.c
int	create_north(t_parsing_data *data);
int	create_south(t_parsing_data *data);
int	create_east(t_parsing_data *data);
int	create_west(t_parsing_data *data);


#endif
