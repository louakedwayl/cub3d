/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:15:31 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/29 20:46:55 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define WINDOW_WIDTH 700
# define WINDOW_HEIGHT 700

# define TRUE 1
# define FALSE 0
typedef int	t_bool;

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

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

// main data for cub3d
typedef struct s_data
{
	t_mlx_data	*mlx_data;
	char		**map;
	int			map_width;
	int			map_height;
	int			FOV;
}	t_data;

// FOLDER - - - - - - - - - ray_casting - - - - - - - - -

//raycast.c
void	raycast(t_data *data);

#endif
