/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/30 15:05:04 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void start_game(t_parsing_data *parsing_data)
{
	(void) parsing_data;

	t_data	data;

	data.FOV = 60;

	data.map = (char **)malloc(sizeof(char *) * 7);  // 7 map rows

	data.map_height = 7;
	data.map_width = 8;

	// MAP TEST        - X -     |
	data.map[0] = "11111111"; // Y
	data.map[1] = "10000001"; // |
	data.map[2] = "10110001";
	data.map[3] = "10000S01"; // S for spawn
	data.map[4] = "10100001";
	data.map[5] = "10000101";
	data.map[6] = "11111111";

	data.player_pos = make_point(600, 400); /// A CALCULER RELATIVEMENT A LA WINDOW SIZE ET MAP SIZE
	data.player_look_direction = 0;

	raycast(&data);




}
