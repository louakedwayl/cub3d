/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:36 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/31 04:05:36 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_window(t_data *data)
{
	// printf("refreshing\n");

	if (data->mlx_data->img)
		mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);

	data->mlx_data->img = mlx_new_image(data->mlx_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	int start_angle = data->player_look_angle - data->FOV/2;
	int end_angle = data->player_look_angle + data->FOV/2;

	// printf("start_angle : %i\n", start_angle);
	// printf("end_angle : %i\n", end_angle);

	while (start_angle < end_angle)
	{
		process_raycasting(data, start_angle);

		start_angle++;

		//start_angle += 1000;
	}

	draw_square_around_playerpos(data);

	draw_map(data); // j'aimerais éviter de le faire à chaque fois vu que c'est fixe

	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win, data->mlx_data->img, 0, 0);
}

void	draw_map(t_data *data)
{
	t_2dpoint	square_center;
	int			index;
	int			row;

	index = 0;
	row = 0;

	while (row < data->map_height)
	{
		index = 0;
		while (index < data->map_width)
		{
			if (data->map[row][index] == '1')
			{
				square_center = make_point(index, row);
				convert_map_coords_to_window_coords(data, &square_center);
				draw_square_around_point(data, square_center);
			}
			index++;
		}
		row++;
	}
}

// only int as inputs
void forward_ray(t_2dpoint_float *ray, int angle)
{
	// printf("angle : %i\n", angle);
	// printf("from : ");
	// print_point(*ray);

    float angle_rad = ((float)angle) * (M_PI / 180.0);
    float step = 3;  // Un pas plus fin pour la précision

    // Calculs avec des flottants
    float new_x = ray->x + cos(angle_rad) * step;
    float new_y = ray->y + sin(angle_rad) * step;

    ray->x = new_x;
    ray->y = new_y;

	// printf("to : ");
	// print_point(*ray);
}

// Custom Ray casting
int process_raycasting(t_data *data, int cast_angle)
{
	t_2dpoint_float	ray;
	int				angle;

	float x = (float)data->player_pos.x;
	float y = (float)data->player_pos.y;

	ray = make_float_point(x, y);
	
	angle = cast_angle; //data->player_look_angle;

	int i = 0;
	while (i < 100)
    {
		// printf("%i - ", i);
		// usleep(100000);

		// printf("player orientation : %i\n", data->player_look_angle);
		
		draw_debug_red_square(data, ray);
		forward_ray(&ray, angle);

		
		//print_point(ray);
		i++;
	}

	return 0;
}

void	raycast(t_data *data)
{
	//* CREATE / INIT
	data->mlx_data = init_mlx_data(data);
	if (!data->mlx_data)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");

	//, BUILD IMAGE

	draw_map(data);
	update_window(data);




	//. LOAD
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win, data->mlx_data->img, 0, 0);
	
	// mlx_key_hook(data->mlx_data->win, key_hook, data);

	mlx_hook(data->mlx_data->win, 2, 1L << 0, key_hook, data); // KeyPress (touche enfoncée)
	// mlx_hook(data->mlx_data->win, 3, 1L << 1, key_release_hook, data); // KeyRelease (touche relâchée)

	mlx_hook(data->mlx_data->win, TOP_RIGHT_CROSS, 0, esc_destroy_all, data);

	mlx_hook(data->mlx_data->win, 6, 1L << 6, mouse_move_hook, data);

	mlx_loop(data->mlx_data->mlx);

	//! DESTROY / EXIT
	free_all_and_exit(data, EXIT_SUCCESS, NULL);
}
