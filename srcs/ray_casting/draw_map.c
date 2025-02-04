/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:39:01 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:39:22 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	trace_square(t_data *data, int index, int row)
{
	t_2dpoint_float	square_center;
	t_2dpoint		point;

	square_center = make_float_point((float)index
			+ 0.5f, (float)row + 0.5f);
	convert_map_coords_to_window_coords_float(data, &square_center);
	if (data->mode_mini)
		minimise_point_float(data, &square_center);
	point = point_float_to_int(square_center);
	if ((index != 0 && row != 0)
		&& (index != data->map_width - 1
			&& row != data->map_height - 1))
		draw_square_around_point(data, point);
}

void	draw_map(t_data *data)
{
	int				index;
	int				row;

	index = 0;
	row = 0;
	while (row < data->map_height)
	{
		index = 0;
		while (index < data->map_width)
		{
			if (data->map[row][index] == '1')
			{
				trace_square(data, index, row);
			}
			index++;
		}
		row++;
	}
}
