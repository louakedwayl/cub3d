/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 18:25:29 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void start_game(t_parsing_data *parsing_data)
{
	(void) parsing_data;

	t_data	data;

	data.FOV = 65;

	data.map = (char **)malloc(sizeof(char *) * 8);  // 7 map rows

	data.map_height = 8;
	data.map_width = 8;

	//! Attention faire une fonction qui put des angles pour pa segfault
	// MAP TEST        - X -     |
	data.map[0] = "11111111"; // Y
	data.map[1] = "10000001"; // |
	data.map[2] = "10100101";
	data.map[3] = "10000E01"; // S for spawn
	data.map[4] = "10010001";
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

	data.square_size = (float) data.map_height * 11.0f;

	data.rc.last_orientation = NORTH;
	data.rc.print_limit_count = 0;
	data.rc.debug_print_each = 60;
	data.rc.debug_print_limit = 50;
	data.rc.render_distance = 100000;

	raycast(&data);



}
