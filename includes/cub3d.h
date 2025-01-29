

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"

# define WINDOW_WIDTH 700
# define WINDOW_HEIGHT 700

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

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


typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}						t_img;

typedef struct s_data
{
	int		fd;
	char	**map;
	char	*north;
	char	*west;
	char	*south;
	char	*east;
	void	*mlx;
	void	*mlx_win;
	int		floor[2];
	int		ceiling[2];
	t_img	img_north;
	t_img	img_west;
	t_img	img_south;
	t_img	img_east;
}				t_data;

// FOLDER - - - - - - - - - ray_casting - - - - - - - - -

//raycast.c
void	raycast(t_data *data);

// check_args.c
int				check_nbr_arg(int argc);
int 			check_name_map(char **argv);
int				open_map(t_data *data, char *map);

#endif
