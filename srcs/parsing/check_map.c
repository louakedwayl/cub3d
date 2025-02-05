/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:03:34 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/05 17:36:57 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int norm_search(int	player_nbr)
{
	if (player_nbr != 1)
	{
		printf ("Error: It should have only one player\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_search_player(t_parsing_data *data)
{
	int row;
	int col;
	int player_nbr;

	row = 0;
	player_nbr = 0;
	while (data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
				if (data->map[row][col] == 'N')
				{
					player_nbr++;
					data->player_y = row;
					data->player_x = col;
					return (EXIT_SUCCESS);
				}
			col++;
		}
		row++;
	}
	norm_search(player_nbr);
	return (EXIT_FAILURE);
}


int check_map(t_parsing_data *data)
{
	char **clone;

	clone = NULL;
	ft_set_xmax(data);
	ft_set_ymax(data);
	ft_search_player(data);
	clone = ft_strrdup(data->map);
	if (!clone)
	{
		printf ("Error: parse error\n");
		return (EXIT_FAILURE);
	}
	if (ft_fill(data, clone, data->player_x, data->player_y))
	{
		clear_map(clone);
		printf ("Error: map invalid\n");
		return (EXIT_FAILURE);
	}
	clear_map(clone);
	return (EXIT_SUCCESS);
}


int	ft_fill(t_parsing_data *data, char **clone,  int x, int y)
{
	if (x < 0 || x >= data->xmax || y < 0
		|| y >= data->ymax )
		return (EXIT_FAILURE);
	if (clone[y][x] == '1' || data->map[y][x] == 'V')
		return (EXIT_SUCCESS);
	if (data->map[y][x] == '0' || data->map[y][x] == 'N' || 
		data->map[y][x] == 'E' || data->map[y][x] == 'W' ||
		data->map[y][x] == 'S')
		data->map[y][x] = 'V';
	else
		return (EXIT_FAILURE);
	if (ft_fill( data, clone, x + 1, y)
		|| ft_fill(data, clone, x - 1, y) || ft_fill (data, clone, x, y + 1)
		|| ft_fill(data, clone, x, y - 1))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
