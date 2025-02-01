/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:36 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 17:51:39 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// only int as inputs
void forward_ray(t_2dpoint_float *ray, float angle)
{
	// printf("angle : %i\n", angle);
	// printf("from : ");
	// print_point(*ray);

    float angle_rad = ((float)angle) * (M_PI / 180.0);
    float step = 0.5;  // Un pas plus fin pour la précision

    // Calculs avec des flottants
    float new_x = ray->x + cos(angle_rad) * step;
    float new_y = ray->y + sin(angle_rad) * step;

    ray->x = new_x;
    ray->y = new_y;

	// printf("to : ");
	// print_point(*ray);
}

void	init_raycast_vars(t_data *data)
{
	data->rc.print_limit_count++;
	if (data->rc.print_limit_count > data->rc.debug_print_limit)
	{
		data->rc.print_limit_count = 0;
	}
	else
		data->rc.print_limit_count++;
	data->rc.x = (float)data->player_pos.x;
	data->rc.y = (float)data->player_pos.y;
	data->rc.ray = make_float_point(data->rc.x, data->rc.y);
	data->rc.i = 0;
}

void	update_ray(t_data *data, float cast_angle)
{
	if (data->debug_mode && data->rc.i % data->rc.debug_print_each == 0 && data->rc.print_limit_count == data->rc.debug_print_limit)
	{
		data->debug_color = 0xc91c1c; // red
		draw_debug_square(data, data->rc.ray, 2);
	}
	if (data->mode_mini && data->rc.i % data->rc.debug_print_each == 0 && data->rc.print_limit_count == data->rc.debug_print_limit)
	{
		data->debug_color = 0xc91c1c; // red
		draw_debug_square(data, data->rc.ray, 1);
	}
	forward_ray(&data->rc.ray, cast_angle);
	data->rc.hit_point = data->rc.ray; // point_float_to_int(ray);
	data->rc.on_map_float = data->rc.ray; // point_float_to_int(ray);
	convert_window_coords_to_map_coords_float(data, &data->rc.on_map_float);
	data->rc.on_map = point_float_to_int(data->rc.on_map_float);
}

void	setup_collision_vars(t_data *data)
{
	// printf("hit\n");
	//. COLLISION AXE
	// hit_point;

	convert_map_coords_to_window_coords(data, &data->rc.on_map);
	data->rc.on_map.x += data->square_size / 2.0f;
	data->rc.on_map.y += data->square_size / 2.0f;
	data->rc.on_map_float = make_float_point((float)data->rc.on_map.x, (float)data->rc.on_map.y);

	// printf("x\n");
	// print_point(on_map);
	// print_point(hit_point);

	if (data->debug_mode)
	{
		data->debug_color = ORANGE;
		draw_debug_square(data, data->rc.on_map_float, 5);
	}
}

// EAST WEST
void	get_vertical_hit_infos(t_data *data)
{
	if (data->rc.hit_point.x > data->rc.on_map_float.x)
	{
		data->debug_color = 0x00ccff; // blue
		data->wall_orientation = EAST;
	}
	else
	{
		data->debug_color = 0xffff00; // yellow
		data->wall_orientation = WEST;
	}
	data->hit_part = (data->rc.hit_point.y - data->rc.on_map_float.y);
}

// NORTH SOUTH
void	get_horizontal_hit_infos(t_data *data)
{
	if (data->rc.hit_point.y < data->rc.on_map_float.y)
	{
		data->debug_color = 0x9900ff; // purple
		data->wall_orientation = SOUTH;
	}
	else
	{
		data->debug_color = 0xffffff; // white
		data->wall_orientation = NORTH;
	}
	data->hit_part = (data->rc.hit_point.x - data->rc.on_map_float.x);
}

void	get_collision_infos(t_data *data)
{
	setup_collision_vars(data);

	if (fabs(data->rc.hit_point.x - data->rc.on_map_float.x) > fabs(data->rc.hit_point.y - data->rc.on_map_float.y))  
		get_vertical_hit_infos(data);
	else
		get_horizontal_hit_infos(data);

	// if (data->debug_mode)
	// 	printf("hit part : %f\n", data->hit_part);

	// avoid corner bug
	if (fabs(fabs(data->rc.hit_point.x - data->rc.on_map_float.x) - fabs(data->rc.hit_point.y - data->rc.on_map_float.y)) <= 2.0f)
		data->wall_orientation = data->rc.last_orientation;
	data->rc.last_orientation = data->wall_orientation;


	if (data->debug_mode)
		draw_debug_square(data, data->rc.ray, 2);
}

// Custom Ray casting
int process_raycasting(t_data *data, float cast_angle)
{
	init_raycast_vars(data);

	while (data->rc.i < data->rc.render_distance)
    {
		// printf("%i - ", i);
		// usleep(100000);

		// printf("player orientation : %i\n", data->player_look_angle);

		update_ray(data, cast_angle);

		if (data->map_height >= data->rc.on_map.y && data->map_width >= data->rc.on_map.x)
		{
			if (data->map[data->rc.on_map.y][data->rc.on_map.x] == '1')
			{
				get_collision_infos(data);

				return (get_distance(data->player_pos, point_float_to_int(data->rc.hit_point)));
			}
		}
		data->rc.i++;
	}

	return 0;
}

void	load_game(t_data *data)
{
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win, data->mlx_data->img, 0, 0);
	mlx_hook(data->mlx_data->win, 2, 1L << 0, key_hook, data); // KeyPress (touche enfoncée)
	mlx_hook(data->mlx_data->win, TOP_RIGHT_CROSS, 0, esc_destroy_all, data);
	mlx_hook(data->mlx_data->win, 6, 1L << 6, mouse_move_hook, data);
	data->key_hook_active = TRUE;
	mlx_loop(data->mlx_data->mlx);
}

void	raycast(t_data *data)
{
	//* CREATE / INIT
	data->mlx_data = init_mlx_data(data);
	if (!data->mlx_data)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");
	mlx_mouse_get_pos(data->mlx_data->mlx, data->mlx_data->win, &data->last_x, &data->last_y);

	//, BUILD IMAGE
	draw_map(data);
	update_window(data);

	//. LOAD
	load_game(data);

	//! DESTROY / EXIT
	free_all_and_exit(data, EXIT_SUCCESS, NULL);
}
