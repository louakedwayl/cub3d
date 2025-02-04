/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:20:48 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// custom realloc
char	*ft_allocplus(char *buffer, size_t size)
{
	char	*new_buffer;
	size_t	n;

	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	n = ft_strlen(buffer);
	new_buffer = malloc(n + size + 1);
	if (!new_buffer)
		return (NULL);
	ft_memcpy(new_buffer, buffer, n);
	free(buffer);
	buffer = NULL;
	new_buffer[n] = '\0';
	return (new_buffer);
}

int	get_longest_line(char **map)
{
	int	longest_line;
	int	i;

	if (!map || !map[0])
		return (0);

	longest_line = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > longest_line)
			longest_line = (int)ft_strlen(map[i]);
		i++;
	}
	return (longest_line);
}

int	get_map_height(char **map)
{
	int	i;

	if (!map || !map[0])
		return (0);

	i = 0;
	while (map[i])
		i++;
	return (i);
}

// make a '1' circle around the map to cover rays to path through
t_bool	transform_to_square_and_cover(t_data *data, char **map)
{
	char	**newmap;
	int		i;
	int		max;

	if (!map || !map[0])
		return (FALSE);
	
	if (data->map_height > data->map_width)
		max = data->map_height;
	else
		max = data->map_width;
	
	max += 2; //. Pour la cover

	newmap = (char **)ft_calloc(max + 1, sizeof(char *));
	if (!newmap)
		return (FALSE);

	// printf("max : %i\n", max);
	
	i = 0;
	while (i < max)
	{
		newmap[i] = (char *)calloc(max, sizeof(char *));
		{
			if (!newmap[i])
			{
				clear_map(newmap);
				return (FALSE);
			}
		}
		newmap[i][0] = '1';
		// newmap[i][max - 1] = '1';
		newmap[i][max] = '\0';

		if (i == 0 || i == max - 1)
		{
			ft_memset(&newmap[i][1], '1', max - 1);
		}
		else if (i - 1 < data->map_height)
		{
			ft_strlcpy(&(newmap[i][1]), map[i - 1], ft_strlen(map[i - 1]) + 1);

			int n = ft_strlen(map[i - 1]) + 1;
			while (n < max)
			{
				newmap[i][n] = ' ';
				n++;
			}
		}
		else
		{
			ft_memset(&newmap[i][1], ' ', max - 1);
		}
		
		newmap[i][max - 1] = '1';

		// printf("%i - %s\n", i, newmap[i]);
	
		i++;
	}

	// printf("check\n");

	// sleep(10);

	data->map_height = max;
	data->map_width = max;

	data->map = newmap;

	clear_map(map);  // CLEAR L'ANCIENNE

	return (TRUE);

	// ! clear_map(map);  // CLEAR L'ANCIENNE
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
				if (map[y][x] == 'N')
					data->player_look_angle = -90;
				else if (map[y][x] == 'E')
					data->player_look_angle = 0;
				else if (map[y][x] == 'S')
					data->player_look_angle = 90;
				else
					data->player_look_angle = 180;
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
	// data->player_look_angle = 0;
	data->player_vertical_look = 0;
	data->key_hook_active = FALSE;
	data->mode_mini = FALSE;
	data->mini_scale = 5;
	data->mini_offset = 30;
	data->square_size = (float) ((float)WINDOW_HEIGHT / (float)data->map_height);
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
	if (transform_to_square_and_cover(&data, data.map) == FALSE)
		free_all_and_exit(&data, EXIT_SUCCESS, NULL);
	data.debug_color = 0xffffff;
	player_pos = get_player_spawn_point(&data, data.map);
	convert_map_coords_to_window_coords(&data, &player_pos);
	data.debug_mode = FALSE;
	data.player_pos = player_pos;
	init_data_vars(&data);
	raycast(&data);
}
