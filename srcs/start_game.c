/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:56:41 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_angle(t_data *data, char c)
{
	if (c == 'N')
		data->player_look_angle = -90;
	else if (c == 'E')
		data->player_look_angle = 0;
	else if (c == 'S')
		data->player_look_angle = 90;
	else
		data->player_look_angle = 180;
}

t_2dpoint	get_player_spawn_point(t_data *data, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!map || !map[0])
		free_all_and_exit(data, EXIT_FAILURE, NULL);
	while (map[y])
	{
		x = 0;
		while (map[x])
		{
			if ((map[y][x] != '0') && (map[y][x] != '1') && (map[y][x] != ' '))
			{
				set_player_angle(data, map[y][x]);
				return (make_point(x, y));
			}
			x++;
		}
		y++;
	}
	free_all_and_exit(data, EXIT_FAILURE, "no spawnpoint was found");
	return (make_point(5, 5));
}

void	init_data_vars(t_data *data)
{
	data->player_vertical_look = 0;
	data->key_hook_active = FALSE;
	data->mode_mini = FALSE;
	data->mini_scale = 5;
	data->mini_offset = 30;
	data->square_size = (float)((float)WINDOW_HEIGHT / (float)data->map_height);
	data->player_pos.x += (int)(data->square_size / 2.0f);
	data->player_pos.y += (int)(data->square_size / 2.0f);
	data->rc.last_orientation = NORTH;
	data->rc.print_limit_count = 0;
	data->rc.debug_print_limit = 2;
	data->rc.render_distance = 1000;
}

void	start_game(t_parsing_data *parsing_data)
{
	t_data		data;
	t_2dpoint	player_pos;

	data.parsing_data = parsing_data;
	data.FOV = 65;
	data.map = data.parsing_data->map;
	data.map_height = get_map_height(data.map);
	data.map_width = get_longest_line(data.map);
	if (transform_to_square_and_cover(&data) == FALSE)
		free_all_and_exit(&data, EXIT_SUCCESS, NULL);
	data.debug_color = 0xffffff;
	player_pos = get_player_spawn_point(&data, data.map);
	convert_map_coords_to_window_coords(&data, &player_pos);
	data.debug_mode = FALSE;
	data.player_pos = player_pos;
	init_data_vars(&data);
	raycast(&data);
}
