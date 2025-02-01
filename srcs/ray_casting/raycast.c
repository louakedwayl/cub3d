/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:36 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 17:34:34 by ajosse           ###   ########.fr       */
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

// Custom Ray casting
int process_raycasting(t_data *data, float cast_angle)
{
	static int last_orientation = NORTH;

	static int print_limit_count = 0; // ça en print 1 sur 10

	int debug_print_each = 60; // ça en print 1 tous les x step
	int debug_print_limit = 50; // ça en print 1 sur x


	print_limit_count++;
	if (print_limit_count > debug_print_limit)
	{
		print_limit_count = 0;
	}
	else
		print_limit_count++;

	t_2dpoint_float	ray;
	t_2dpoint_float	hit_point;
	t_2dpoint_float	on_map_float;
	t_2dpoint		on_map;

	float x = (float)data->player_pos.x;
	float y = (float)data->player_pos.y;
	ray = make_float_point(x, y);

	int render_distance = 100000;

	int i = 0;
	while (i < render_distance)
    {
		// printf("%i - ", i);
		// usleep(100000);

		// printf("player orientation : %i\n", data->player_look_angle);

		if (data->debug_mode && i % debug_print_each == 0 && print_limit_count == debug_print_limit)
		{
			data->debug_color = 0xc91c1c; // red
			draw_debug_square(data, ray, 2);
		}

		if (data->mode_mini && i % debug_print_each == 0 && print_limit_count == debug_print_limit)
		{
			data->debug_color = 0xc91c1c; // red
			draw_debug_square(data, ray, 1);
		}

		forward_ray(&ray, cast_angle);

		hit_point = ray; // point_float_to_int(ray);
		on_map_float = ray; // point_float_to_int(ray);
		convert_window_coords_to_map_coords_float(data, &on_map_float);

		on_map = point_float_to_int(on_map_float);

		if (data->map_height >= on_map.y && data->map_width >= on_map.x)
		{
			if (data->map[on_map.y][on_map.x] == '1')
			{
				// printf("hit\n");

                //. COLLISION AXE
				
				// hit_point;

				convert_map_coords_to_window_coords(data, &on_map);

				on_map.x += data->square_size / 2.0f;
				on_map.y += data->square_size / 2.0f;

				on_map_float = make_float_point((float)on_map.x, (float)on_map.y);

				// printf("x\n");
				// print_point(on_map);
				// print_point(hit_point);

				if (data->debug_mode)
				{
					data->debug_color = ORANGE;
					draw_debug_square(data, on_map_float, 5);
				}

				if (fabs(hit_point.x - on_map_float.x) > fabs(hit_point.y - on_map_float.y))  
				{
					if (hit_point.x > on_map_float.x)
					{
						data->debug_color = 0x00ccff; // blue
						data->wall_orientation = EAST;
					}
					else
					{
						data->debug_color = 0xffff00; // yellow
						data->wall_orientation = WEST;
					}
					data->hit_part = (hit_point.y - on_map_float.y);
				}
				else  
				{
					if (hit_point.y < on_map_float.y)
					{
						data->debug_color = 0x9900ff; // purple
						data->wall_orientation = SOUTH;
					}
					else
					{
						data->debug_color = 0xffffff; // white
						data->wall_orientation = NORTH;
					}
					data->hit_part = (hit_point.x - on_map_float.x);
				}

				// if (data->debug_mode)
				// 	printf("hit part : %f\n", data->hit_part);

				// avoid corner bug
				if (fabs(fabs(hit_point.x - on_map_float.x) - fabs(hit_point.y - on_map_float.y)) <= 2.0f)
					data->wall_orientation = last_orientation;
				last_orientation = data->wall_orientation;


				if (data->debug_mode)
					draw_debug_square(data, ray, 2);

				return (get_distance(data->player_pos, point_float_to_int(hit_point)));
			}
		}
		i++;
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
