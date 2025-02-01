/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:36 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 01:14:00 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		get_distance(t_2dpoint a, t_2dpoint b)
{
    // Calcul de la différence des coordonnées
    int dx = b.x - a.x;
    int dy = b.y - a.y;

    // Calcul de la distance euclidienne
    return (int)sqrt(dx * dx + dy * dy);  // Utilisation de sqrt pour la racine carrée
}

int		get_distance_float(t_2dpoint_float a, t_2dpoint_float b)
{
    // Calcul de la différence des coordonnées
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    // Calcul de la distance euclidienne
    return (int)sqrt((double)dx * (double)dx + (double)dy * (double)dy);  // Utilisation de sqrt pour la racine carrée
}

// big distance = small column    because far
void	draw_pixel_column(t_data *data, int column, int distance)
{
    // Hauteur de l'écran (en pixels)
    int screen_height = WINDOW_HEIGHT;
    // La distance de projection (valeur arbitraire, peut être ajustée)
    float view_distance = 50.0f;  // Distance de la caméra à la scène (fixée ou dynamique)

    // Calcul de la hauteur de la colonne pour la projection 3D
    float column_height = (screen_height * view_distance) / (float)distance;

    // Calcul de l'offset vertical pour centrer la colonne sur l'écran
    int top = (screen_height - (int)column_height) / 2;
    int bottom = top + (int)column_height;

	// printf("top : %i\n", top);
	// printf("bottom : %i\n", bottom);

	// printf("column : %i\n", column);
	// printf("screen_height : %i\n", screen_height);

	t_2dpoint x = make_point(column, top);
	t_2dpoint y = make_point(column, bottom); // plus grande valeur car en bas

	t_2dpoint ceilling = make_point(column, 0);
	t_2dpoint floor = make_point(column, WINDOW_HEIGHT);

	draw_line(data, x, y, 0x7b13a8);		// mur
	draw_line(data, y, floor, 0x3a333d);	// sol
	draw_line(data, ceilling, x, 0x88a6a2); // ciel

    // // Dessiner la colonne
    // for (int y = 0; y < screen_height; y++)
    // {
    //     if (y < top)
	// 	{
    //         put_pixel_on_image(data, column, y, 0x0);  // Fond
	// 	}
    //     else if (y >= top && y < bottom)
	// 	{
	// 		// printf("wall in : (%i, %i)\n", column, y);
    //         put_pixel_on_image(data, column, y, 0x7b13a8);  // Mur
	// 	}
    //     else
	// 	{
    //         put_pixel_on_image(data, column, y, 0x6a4ae8);  // Ciel
	// 	}
    // }
}

void	update_window(t_data *data)
{
	// printf("refreshing\n");

	int distance;
	int column;
	int start_angle;
	int end_angle;

	if (data->mlx_data->img)
		mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);

	data->mlx_data->img = mlx_new_image(data->mlx_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	start_angle = data->player_look_angle - data->FOV/2;
	end_angle = data->player_look_angle + data->FOV/2;

	// printf("start_angle : %i\n", start_angle);
	// printf("end_angle : %i\n", end_angle);

	int i;

	i = 0;

	column = 0;
	while (start_angle < end_angle)
	{
		distance = process_raycasting(data, start_angle);

		// printf("distance : %i\n", distance);

		i = 0;
		if (distance > 10)
		{
			while (i < 12)
			{
				// draw_pixel_column(data, column, distance); //, DRAW
				i++;
				column++;
			}
		}
		else
			column += 1;
		
		// printf("start_angle : %i\n", start_angle);

		start_angle++;

		//start_angle += 1000;
	}

	//draw_square_around_playerpos(data);

	draw_map(data); // j'aimerais éviter de le faire à chaque fois vu que c'est fixe

	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win, data->mlx_data->img, 0, 0);

	sleep(0.1);

	usleep(1000);
}

void	draw_map(t_data *data)
{
	t_2dpoint_float	square_center;
	t_2dpoint	point;
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
				square_center = make_float_point((float)index + 0.5f, (float)row + 0.5f);
				convert_map_coords_to_window_coords_float(data, &square_center);
				point = point_float_to_int(square_center);
				draw_square_around_point(data, point);
			}
			index++;
		}
		row++;
	}
}

// only int as inputs
void forward_ray(t_data *data, t_2dpoint_float *ray, int angle)
{
	// printf("angle : %i\n", angle);
	// printf("from : ");
	// print_point(*ray);

    float angle_rad = ((float)angle) * (M_PI / 180.0);
    float step = 1;  // Un pas plus fin pour la précision

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
	t_2dpoint_float	on_window;
	t_2dpoint_float	on_map;

	t_2dpoint	int_point;

	t_2dpoint_float	ray;
	int				angle;

	float x = (float)data->player_pos.x;
	float y = (float)data->player_pos.y;

	ray = make_float_point(x, y);
	
	angle = cast_angle; //data->player_look_angle;

	int render_distance = 1000;

	int i = 0;
	while (i < render_distance)
    {
		// printf("%i - ", i);
		// usleep(100000);

		// printf("player orientation : %i\n", data->player_look_angle);

		if (DEBUG)
		{
			data->debug_color = 0xc91c1c; // red
			draw_debug_square(data, ray);
		}

		forward_ray(data, &ray, angle);

		on_window = ray; //point_float_to_int(ray);
		on_map = ray; // point_float_to_int(ray);
		convert_window_coords_to_map_coords_float(data, &on_map);

		int_point = point_float_to_int(on_map);

		if (data->map_height >= on_map.y && data->map_width >= on_map.x)
		{
			if (data->map[int_point.y][int_point.x] == '1')
			{
				// printf("hit\n");
				if (DEBUG)
					draw_debug_square(data, ray);

				return (get_distance(data->player_pos, point_float_to_int(on_window)));
			}
		}

		//print_point(ray);
		i++;
	}

	return 0;
}

/*
	if (DEBUG)
	{
		if (angle_rad < M_PI)
			data->debug_color = 0x50ff2f; // green
		else if (angle_rad < 180)
			data->debug_color = 0x502fff; // blue cyan
		else if (angle_rad < 270)
			data->debug_color = 0x9900ff; // dark blue
		else
			data->debug_color = 0xff50ff; // purple
	}
*/



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
    // mlx_mouse_move(data->mlx_data->mlx, data->mlx_data->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // Place la souris au centre
    // mlx_mouse_hide(data->mlx_data->mlx, data->mlx_data->win); // Cache le curseur

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
