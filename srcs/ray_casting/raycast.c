/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:36 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:34:15 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_near_corner(float x, float y, float square_size)
{
	float	marge;
	float	mod_x;
	float	mod_y;
	int		close_to_x;
	int		close_to_y;

	marge = 1.0f;
	mod_x = fmodf(x, square_size);
	mod_y = fmodf(y, square_size);
	close_to_x = (mod_x <= marge || fabsf(mod_x - square_size) <= marge);
	close_to_y = (mod_y <= marge || fabsf(mod_y - square_size) <= marge);
	return (close_to_x && close_to_y);
}

t_bool	point_is_in_wall(t_data *data, t_2dpoint_float point)
{
	t_2dpoint_float	on_map;
	t_2dpoint		on_map_int;

	on_map = make_float_point((float)point.x, (float)point.y);
	convert_window_coords_to_map_coords_float(data, &on_map);
	on_map_int = point_float_to_int(on_map);
	if (data->map_height >= on_map_int.y && data->map_width >= on_map_int.x)
	{
		if (data->map[on_map_int.y][on_map_int.x] == '1')
			return (TRUE);
	}
	return (FALSE);
}

// Custom Ray casting
float	process_raycasting(t_data *data, float cast_angle)
{
	t_2dpoint_float	temp;

	init_raycast_vars(data);
	while (data->rc.i < data->rc.render_distance)
	{
		update_ray(data, cast_angle);
		if (point_is_in_wall(data, data->rc.ray))
		{
			if (is_near_corner(data->rc.ray.x,
					data->rc.ray.y, data->square_size))
				data->wall_orientation = data->rc.last_orientation;
			data->rc.last_orientation = data->wall_orientation;
			if (data->debug_mode)
				draw_debug_square(data, data->rc.hit_point, 2);
			temp = make_float_point((float)data->player_pos.x,
					(float)data->player_pos.y);
			return (get_distance_float(temp, data->rc.hit_point));
		}
		data->rc.i++;
	}
	return (0);
}

void	load_game(t_data *data)
{
	mlx_put_image_to_window(data->mlx_data->mlx,
		data->mlx_data->win, data->mlx_data->img, 0, 0);
	mlx_hook(data->mlx_data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->mlx_data->win, TOP_RIGHT_CROSS, 0, esc_destroy_all, data);
	mlx_hook(data->mlx_data->win, 6, 1L << 6, mouse_move_hook, data);
	data->key_hook_active = TRUE;
	mlx_loop(data->mlx_data->mlx);
}

void	raycast(t_data *data)
{
	data->mlx_data = init_mlx_data(data);
	if (!data->mlx_data)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");
	mlx_mouse_get_pos(data->mlx_data->mlx,
		data->mlx_data->win, &data->last_x, &data->last_y);
	draw_map(data);
	update_window(data);
	load_game(data);
	free_all_and_exit(data, EXIT_SUCCESS, NULL);
}
