/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:36 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/03 05:57:10 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// // only int as inputs
// void forward_ray(t_2dpoint_float *ray, float angle)
// {
// 	// printf("angle : %i\n", angle);
// 	// printf("from : ");
// 	// print_point(*ray);

//     float angle_rad = ((float)angle) * (M_PI / 180.0);
//     float step = 0.5;  // Un pas plus fin pour la précision

//     // Calculs avec des flottants
//     float new_x = ray->x + cos(angle_rad) * step;
//     float new_y = ray->y + sin(angle_rad) * step;

//     ray->x = new_x;
//     ray->y = new_y;

// 	// printf("to : ");
// 	// print_point(*ray);
// }

t_bool	point_is_in_wall(t_data *data, t_2dpoint_float point)
{
	t_2dpoint_float on_map;
	t_2dpoint		on_map_int;

	on_map = make_float_point((float)point.x, (float)point.y);
	convert_window_coords_to_map_coords_float(data, &on_map);
	on_map_int = point_float_to_int(on_map);

	if (data->map_height >= on_map_int.y && data->map_width >= on_map_int.x)
	{
		if (data->map[on_map_int.y][on_map_int.x] == '1')
			return TRUE;
	}
	return FALSE;
}

void forward_ray(t_data *data, t_2dpoint_float *ray, float angle)
{
	// static int calculs;
	// calculs++;

	// printf("%i\n", calculs);
	
	float angle_rad = angle * (M_PI / 180.0f);
	float dx = (float) cos(angle_rad);
	float dy = (float) sin(angle_rad);

	float distance;

	// printf("avant\n");

	t_2dpoint_float on_map = make_float_point(ray->x, ray->y);
	convert_window_coords_to_map_coords_float(data, &on_map);

	// printf("init ");
	// print_point_float(on_map);

	t_2dpoint temp;
	temp = point_float_to_int(on_map);
	convert_map_coords_to_window_coords(data, &temp);

	// printf("temp : ");
	// print_point(temp);

	on_map = make_float_point((float)temp.x, (float)temp.y);

	on_map.x += (float) data->square_size / 2.0f;
	on_map.y += (float) data->square_size / 2.0f;

	// printf("on map : ");
	// print_point_float(on_map);

	// convert_map_coords_to_window_coords_float(data, &on_map); //!

	t_2dpoint_float on_map_cpy = make_float_point(on_map.x, on_map.y);

	// printf("init ");
	// print_point_float(on_map);
	// printf("copy ");
	// print_point_float(on_map_cpy);

	// data->debug_color = 0x00f5FF; // blue cyan
	// draw_debug_square(data, on_map, 3);

	// printf("check\n");

	// int top = 0;
	// int bot = 0;
	// int left = 0;
	// int right = 0;

    // if (dy > 0)
	// 	top = 1;
    // if (dy < 0)
	// 	bot = 1;
    // if (dx > 0)
	// 	right = 1;
    // if (dx < 0)
	// 	left = 1;

	t_2dpoint_float point_x_projection;
	t_2dpoint_float point_y_projection;

	point_x_projection = make_float_point(-1000, -1000);
	point_y_projection = make_float_point(-1000, -1000);

	if (dx != 0)
	{
		// vers droite ou gauche
		if (dx > 0)
		{
			//! vers droite
			on_map.x += data->square_size / 2.0f;
		}
		else
		{
			//* vers gauche
			on_map.x -= data->square_size / 2.0f;
		}
		on_map.y = ray->y;

		// data->debug_color = 0x00ff00; //* green
		// draw_debug_square(data, on_map, 2);

		distance = fabs((on_map.x - ray->x) / dx);
		// ray->x += dx * distance;
		// ray->y += dy * distance;

		point_x_projection.x = ray->x + (dx * distance);
		point_x_projection.y = ray->y + (dy * distance);
	
		// data->debug_color = 0x00ff00; //* green
		// draw_debug_square(data, point_x_projection, 2);

	}
	if (dy != 0)
	{
		// vers haut ou bas
		if (dy < 0)
		{
			//* vers haut
			on_map_cpy.y -= data->square_size / 2.0f;
		}
		else
		{
			//! vers bas
			on_map_cpy.y += data->square_size / 2.0f;
		}
		on_map_cpy.x = ray->x;

		distance = fabs((on_map_cpy.y - ray->y) / dy);
		// ray->x += dx * distance;
		// ray->y += dy * distance;

		point_y_projection.x = ray->x + (dx * distance);
		point_y_projection.y = ray->y + (dy * distance);
	}



	// data->debug_color = 0x00ff00; //* green
	// draw_debug_square(data, point_x_projection, 2);

	// data->debug_color = 0x9003f2; //*rgb(92, 3, 144)
	// draw_debug_square(data, point_y_projection, 2);

	if (get_distance_float((*ray), point_x_projection)
		< get_distance_float((*ray), point_y_projection))
	{
		ray->x = point_x_projection.x;
		ray->y = point_x_projection.y;

		if (dx > 0)
		{
			data->wall_orientation = EAST;
			data->debug_color = 0x00ccff; // blue
		}
		else
		{
			data->wall_orientation = WEST;
			data->debug_color = 0xffff00; // yellow
		}
	}
	else
	{
		ray->x = point_y_projection.x;
		ray->y = point_y_projection.y;

		if (dy > 0)
		{
			data->wall_orientation = SOUTH;
			data->debug_color = 0x9900ff; // purple
		}
		else
		{
			data->wall_orientation = NORTH;
			data->debug_color = 0xffffff; // white
		}
	}

	// if (init_ray.x - ray->x)
	// t_2dpoint_float ray_copy;
	// ray_copy = make_float_point((float)ray->x, (float)ray->y);
	// (void) ray_copy;

	// avancer un peu pour pas rester pile sur le bord

	// static float scaler = 0.1f;

	// scaler += 0.1f;


	// data->debug_color = 0x00ff00; //* green
	// draw_debug_square(data, data->rc.hit_point, 2);

	// float x_step;
	// float y_step;

	// x_step = float_trunc(dx, 1.0f, 99999.0f);
	// y_step = float_trunc(dy, 1.0f, 99999.0f);

	//,
	if (dx > 0)
	{
		//! vers droite
		ray->x += 0.01f;
		// printf("bah on avance merde oh\n");
		//ray->x = ceilf(ray->x);
	}
	else
	{
		//* vers gauche
		ray->x -= 0.01f;
		//ray->x = floorf(ray->x);
	}

	if (dy > 0)
	{
		//! vers bas
		ray->y += 0.01f;
		//ray->y = ceilf(ray->y);
	}
	else
	{
		//* vers haut
		ray->y -= 0.01f;
		//ray->y = floorf(ray->y);
	}
	//,

	data->rc.ray = *ray;

	data->rc.hit_point = data->rc.ray;

	// if (point_is_in_wall(data, *ray))
	// 	scaler = 0.1f;

	// print_point_float(*ray);

	// ray->x = ceilf(ray->x);
	// ray->y = ceilf(ray->y);


	// ray->x += 1; // dx * 5;
	// ray->y += 1; // dy * 5;

	// print_point_float(*ray);
	// data->debug_color = 0x00ff00; //* green
	// draw_debug_square(data, data->rc.ray, 2);

	// sleep(3);
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
	if (data->debug_mode) // && data->rc.print_limit_count == data->rc.debug_print_limit)
	{
		data->debug_color = 0xc91c1c; // red
		draw_debug_square(data, data->rc.ray, 2);
	}
	if (data->mode_mini && data->rc.print_limit_count == data->rc.debug_print_limit)
	{
		data->debug_color = 0xc91c1c; // red
		draw_debug_square(data, data->rc.ray, 1);
	}



	forward_ray(data, &data->rc.ray, cast_angle);


	// data->rc.hit_point = data->rc.ray; // point_float_to_int(ray);

	// data->rc.on_map_float = data->rc.ray; // point_float_to_int(ray);

	// data->rc.on_map_float = make_float_point(ceilf(data->rc.ray.x),ceilf(data->rc.ray.y));




	// data->rc.on_map = point_float_to_int(data->rc.on_map_float);

	// printf("ray : ");
	// print_point_float(data->rc.ray);

	// printf("on_map : ");
	// print_point(data->rc.on_map);


	// printf("angle : %f\n", cast_angle);

	// sleep(0.1);
}

// void	setup_collision_vars(t_data *data)
// {
// 	// printf("hit\n");
// 	//. COLLISION AXE
// 	// hit_point;

// 	convert_map_coords_to_window_coords(data, &data->rc.on_map);
// 	data->rc.on_map.x += data->square_size / 2.0f;
// 	data->rc.on_map.y += data->square_size / 2.0f;
// 	data->rc.on_map_float = make_float_point((float)data->rc.on_map.x, (float)data->rc.on_map.y);

// 	// printf("x\n");
// 	// print_point(on_map);
// 	// print_point(hit_point);

// 	if (data->debug_mode)
// 	{
// 		data->debug_color = ORANGE;
// 		draw_debug_square(data, data->rc.on_map_float, 5);
// 	}
// }

// // EAST WEST
// void	get_vertical_hit_infos(t_data *data)
// {
// 	if (data->rc.hit_point.x > data->rc.on_map_float.x)
// 	{
// 		data->debug_color = 0x00ccff; // blue
// 		data->wall_orientation = EAST;
// 	}
// 	else
// 	{
// 		data->debug_color = 0xffff00; // yellow
// 		data->wall_orientation = WEST;
// 	}
// 	data->hit_part = (data->rc.hit_point.y - data->rc.on_map_float.y);
// }

// // NORTH SOUTH
// void	get_horizontal_hit_infos(t_data *data)
// {
// 	if (data->rc.hit_point.y < data->rc.on_map_float.y)
// 	{
// 		data->debug_color = 0x9900ff; // purple
// 		data->wall_orientation = SOUTH;
// 	}
// 	else
// 	{
// 		data->debug_color = 0xffffff; // white
// 		data->wall_orientation = NORTH;
// 	}
// 	data->hit_part = (data->rc.hit_point.x - data->rc.on_map_float.x);
// }

// void	get_collision_infos(t_data *data)
// {
// 	setup_collision_vars(data);

// 	if (fabs(data->rc.hit_point.x - data->rc.on_map_float.x) > fabs(data->rc.hit_point.y - data->rc.on_map_float.y))  
// 		get_vertical_hit_infos(data);
// 	else
// 		get_horizontal_hit_infos(data);

// 	// if (data->debug_mode)
// 	// 	printf("hit part : %f\n", data->hit_part);

// 	//! avoid corner bug
// 	if ((fabs(fabs(data->rc.hit_point.x - data->rc.on_map_float.x)
// 		- fabs(data->rc.hit_point.y - data->rc.on_map_float.y))
// 		<= 3.0f))
// 	{
// 		data->wall_orientation = data->rc.last_orientation;
// 	}
// 	data->rc.last_orientation = data->wall_orientation;


// 	if (data->debug_mode)
// 		draw_debug_square(data, data->rc.hit_point, 2);
// }

int is_near_corner(float x, float y, float square_size)
{

	float marge = 1.0f;

    float mod_x = fmodf(x, square_size);
    float mod_y = fmodf(y, square_size);

    int close_to_x = (mod_x <= marge || fabsf(mod_x - square_size) <= marge);
    int close_to_y = (mod_y <= marge || fabsf(mod_y - square_size) <= marge);

    return (close_to_x && close_to_y);
}

// Custom Ray casting
float process_raycasting(t_data *data, float cast_angle)
{
	init_raycast_vars(data);

	while (data->rc.i < data->rc.render_distance)
    {
		// printf("%i - ", i);
		// usleep(100000);

		// printf("player orientation : %i\n", data->player_look_angle);

		update_ray(data, cast_angle);

		// print_map(data->map);
		
		if (point_is_in_wall(data, data->rc.ray))
		{

			//! avoid corner bug
			if (is_near_corner(data->rc.ray.x, data->rc.ray.y, data->square_size))
			{
				//printf("avoiding\n");
				data->wall_orientation = data->rc.last_orientation;

				//print_point_float(data->rc.ray);

				// data->debug_color = 0x00ff00; //* green
				// draw_debug_square(data, data->rc.hit_point, 5);
			}
			data->rc.last_orientation = data->wall_orientation;


			if (data->debug_mode)
				draw_debug_square(data, data->rc.hit_point, 2);
			//!



			// get_collision_infos(data);
			t_2dpoint_float temp;
			temp = make_float_point((float)data->player_pos.x, (float)data->player_pos.y);
			return (get_distance_float(temp, data->rc.hit_point));
		}


		// if (data->map_height >= data->rc.on_map.y && data->map_width >= data->rc.on_map.x)
		// {
		// 	if (data->map[data->rc.on_map.y][data->rc.on_map.x] == '1')
		// 	{
		// 		// printf("COLLISION\n");
		// 		get_collision_infos(data);
		// 		return (get_distance(data->player_pos, point_float_to_int(data->rc.hit_point)));
		// 	}
		// }
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
