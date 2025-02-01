/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:10:13 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 17:53:39 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	convert_map_coords_to_window_coords(t_data *data,
											t_2dpoint *point)
{
	point->x = (point->x * WINDOW_WIDTH) / data->map_width;
	point->y = (point->y * WINDOW_HEIGHT) / data->map_height;
}

void	convert_map_coords_to_window_coords_float(t_data *data,
													t_2dpoint_float *point)
{
	point->x = (point->x * (float) WINDOW_WIDTH) / (float) data->map_width;
	point->y = (point->y * (float) WINDOW_HEIGHT) / (float) data->map_height;
}

void	convert_window_coords_to_map_coords(t_data *data,
										t_2dpoint *point)
{
	point->x = (point->x * data->map_width) / WINDOW_WIDTH;
	point->y = (point->y * data->map_height) / WINDOW_HEIGHT;
}

void	convert_window_coords_to_map_coords_float(t_data *data,
													t_2dpoint_float *point)
{
	point->x = (point->x * (float) data->map_width) / (float) WINDOW_WIDTH;
	point->y = (point->y * (float) data->map_height) / (float) WINDOW_HEIGHT;
}
