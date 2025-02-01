/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 06:29:18 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	minimise_point(t_data *data, t_2dpoint *point)
{
	point->x /= data->mini_scale;
	point->y /= data->mini_scale;

	point->x += data->mini_offset;
	point->y += data->mini_offset;
}

void	minimise_point_float(t_data *data, t_2dpoint_float *point)
{
	point->x /= (float) data->mini_scale;
	point->y /= (float) data->mini_scale;

	point->x += (float) data->mini_offset;
	point->y += (float) data->mini_offset;
}

void	convert_map_coords_to_window_coords(t_data *data, t_2dpoint *point)
{
	point->x = (point->x * WINDOW_WIDTH) / data->map_width;
	point->y = (point->y * WINDOW_HEIGHT) / data->map_height;
}

void	convert_map_coords_to_window_coords_float(t_data *data, t_2dpoint_float *point)
{
	point->x = (point->x * (float) WINDOW_WIDTH) / (float) data->map_width;
	point->y = (point->y * (float) WINDOW_HEIGHT) / (float) data->map_height;
}

void convert_window_coords_to_map_coords(t_data *data, t_2dpoint *point)
{
	point->x = (point->x * data->map_width) / WINDOW_WIDTH;
	point->y = (point->y * data->map_height) / WINDOW_HEIGHT;
}

void convert_window_coords_to_map_coords_float(t_data *data, t_2dpoint_float *point)
{
	point->x = (point->x * (float) data->map_width) / (float) WINDOW_WIDTH;
	point->y = (point->y * (float) data->map_height) / (float) WINDOW_HEIGHT;
}

t_2dpoint point_float_to_int(t_2dpoint_float point)
{
	return (make_point(((int)point.x), ((int)point.y)));
}

void start_game(t_parsing_data *parsing_data)
{
	(void) parsing_data;

	t_data	data;

	data.FOV = 60;

	data.map = (char **)malloc(sizeof(char *) * 8);  // 7 map rows

	data.map_height = 8;
	data.map_width = 8;

	// MAP TEST        - X -     |
	data.map[0] = "11111111"; // Y
	data.map[1] = "10000001"; // |
	data.map[2] = "10100101";
	data.map[3] = "10000S01"; // S for spawn
	data.map[4] = "10000001";
	data.map[5] = "11100111";
	data.map[6] = "11111111";
	data.map[7] = "00000000";

	// DERNIERE RANGEE POUR TRANSFORMER EN SQUARE

	data.debug_color = 0xffffff;

	t_2dpoint	player_pos;
	player_pos = make_point(6, 4); // (the S on the map)

	convert_map_coords_to_window_coords(&data, &player_pos);

	data.debug_mode = FALSE;

	data.player_pos = player_pos;


	data.player_look_angle = 0;
	data.player_vertical_look = 0; // milieu


	data.key_hook_active = FALSE;

	data.mode_mini = FALSE;

	data.mini_scale = 5; // bigger = smaller
	data.mini_offset = 30;

	raycast(&data);




}
