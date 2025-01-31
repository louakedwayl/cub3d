/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/31 01:34:57 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	convert_map_coords_to_window_coords(t_data *data, t_2dpoint *point)
{
	point->x = (point->x * WINDOW_WIDTH) / data->map_width;
	point->y = (point->y * WINDOW_HEIGHT) / data->map_height;
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
	data.map[2] = "10110001";
	data.map[3] = "10000S01"; // S for spawn
	data.map[4] = "10100001";
	data.map[5] = "10000101";
	data.map[6] = "11111111";
	data.map[7] = "00000000";

	// DERNIERE RANGEE POUR TRANSFORMER EN SQUARE

	t_2dpoint	player_pos;
	player_pos = make_point(6, 4); // (the S on the map)

	convert_map_coords_to_window_coords(&data, &player_pos);

	if (DEBUG)
	{
		printf("player spawned in : ");
		print_point(player_pos);
	}

	data.player_pos = player_pos;
	data.player_look_angle = 0;

	raycast(&data);




}
