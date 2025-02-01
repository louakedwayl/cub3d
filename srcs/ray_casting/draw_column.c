/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:17:49 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 18:02:54 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	choose_color(t_data *data)
{
	int color;

	if (data->wall_orientation == NORTH)
		color = LIGHT_GRAY;
	else if (data->wall_orientation == SOUTH)
		color = PURPLE;
	else if (data->wall_orientation == EAST)
		color = BLUE;
	else
		color = YELLOW;
	return (color);
}

// big distance = small column    because far
void	draw_pixel_column(t_data *data, int column, int distance)
{

	data->draw_data.screen_height = WINDOW_HEIGHT;
	data->draw_data.view_distance = 50.0f;
	data->draw_data.column_height = (data->draw_data.screen_height * data->draw_data.view_distance) / (float)distance;
	data->draw_data.top = (data->draw_data.screen_height - (int)data->draw_data.column_height) / 2;
	data->draw_data.bottom = data->draw_data.top + (int)data->draw_data.column_height;

	data->draw_data.a = make_point(column, data->draw_data.top);
	data->draw_data.b = make_point(column, data->draw_data.bottom); // plus grande valeur car en bas

	data->draw_data.ceilling = make_point(column, 0);
	data->draw_data.floor = make_point(column, WINDOW_HEIGHT);

	// printf("top : %i\n", top);
	// printf("bottom : %i\n", bottom);

	// printf("column : %i\n", column);
	// printf("screen_height : %i\n", screen_height);

	data->draw_data.a.y -= data->player_vertical_look * 5;
	data->draw_data.b.y -= data->player_vertical_look * 5;
	// ceilling.y -= data->player_vertical_look;
	// floor.y -= data->player_vertical_look;

	data->draw_data.color = choose_color(data);

	draw_line(data, data->draw_data.a, data->draw_data.b, data->draw_data.color);		// mur
	draw_line(data, data->draw_data.b, data->draw_data.floor, 0x3a333d);	// sol
	draw_line(data, data->draw_data.ceilling, data->draw_data.a, 0x88a6a2); // ciel

	// printf("player vertical look : %i\n", data->player_vertical_look);

}
