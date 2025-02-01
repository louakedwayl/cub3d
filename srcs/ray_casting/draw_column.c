/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:17:49 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 17:18:39 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// big distance = small column    because far
void	draw_pixel_column(t_data *data, int column, int distance)
{
    // Hauteur de l'écran (en pixels)
    int screen_height = WINDOW_HEIGHT;
    // La distance de projection (valeur arbitraire, peut être ajustée)
    float view_distance = 50.0f;  // Distance de la caméra à la scène (fixée ou dynamique)

    // Calcul de la hauteur de la colonne pour la projection 3D
    float column_height = (screen_height * view_distance) / (float)distance;

    // Calcul de l'offset vertical pour centrer la colonne sur l'écran
    int top = (screen_height - (int)column_height) / 2;
    int bottom = top + (int)column_height;

	// printf("top : %i\n", top);
	// printf("bottom : %i\n", bottom);

	// printf("column : %i\n", column);
	// printf("screen_height : %i\n", screen_height);

	t_2dpoint a = make_point(column, top);
	t_2dpoint b = make_point(column, bottom); // plus grande valeur car en bas

	t_2dpoint ceilling = make_point(column, 0);
	t_2dpoint floor = make_point(column, WINDOW_HEIGHT);

	a.y -= data->player_vertical_look * 5;
	b.y -= data->player_vertical_look * 5;
	// ceilling.y -= data->player_vertical_look;
	// floor.y -= data->player_vertical_look;

	int color;

	if (data->wall_orientation == NORTH)
		color = LIGHT_GRAY;
	else if (data->wall_orientation == SOUTH)
		color = PURPLE;
	else if (data->wall_orientation == EAST)
		color = BLUE;
	else // if (data->wall_orientation == WEST)
		color = YELLOW;

	draw_line(data, a, b, color);		// mur
	draw_line(data, b, floor, 0x3a333d);	// sol
	draw_line(data, ceilling, a, 0x88a6a2); // ciel

	// printf("player vertical look : %i\n", data->player_vertical_look);

}
