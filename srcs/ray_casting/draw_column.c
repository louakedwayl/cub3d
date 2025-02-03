/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:17:49 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/03 04:01:12 by ajosse           ###   ########.fr       */
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
void	draw_pixel_column(t_data *data, int column, float distance)
{

	data->draw_data.screen_height = WINDOW_HEIGHT;
	data->draw_data.view_distance = data->square_size; // 50.0f;
	data->draw_data.column_height = ((float) data->draw_data.screen_height * data->draw_data.view_distance) / distance;
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

	//. METTRE LA TEXTURE
	/*

	/// Transformer data->hit_part qui va de -data->square_size a data->square_size en 0-1
	float normalized_hit_part = (data->hit_part + data->square_size) / (2 * data->square_size);

	//, 1 FIND X ON TEXTURE
	// data->img_north TYPE t_img
	// data->hit_part; // TYPE int represente la partie du mur hit

	int texture_x = (int)(data->hit_part * texture_width);

	if (texture_x < 0)
		texture_x = 0;
	if (texture_x >= texture_width)
		texture_x = texture_width - 1;
	
	//,2 GET COLOR AT POINT
	int	get_texture_color(t_img *texture, int x, int y)
	{
		char	*pixel;
		int		color;

		pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
		color = *(unsigned int *)pixel;
		return (color);
	}


	//, 3 DRAW
	int line_height = data->draw_data.b.y - data->draw_data.a.y;
	for (int y = data->draw_data.a.y; y < data->draw_data.b.y; y++)
	{
		// Calcul de la coordonnée Y dans la texture
		int d = y * 256 - screen_height * 128 + line_height * 128;  // 256 et 128 sont des facteurs d'échelle
		int texture_y = ((d * texture_height) / line_height) / 256;

		// Obtenir la couleur de la texture
		int color = get_texture_color(&data->img_north, texture_x, texture_y);

		// Dessiner le pixel
		put_pixel_image(data, x, y, color);  // x est la colonne actuelle du rayon
	}


	*/


	data->draw_data.color = choose_color(data);

	draw_line(data, data->draw_data.a, data->draw_data.b, data->draw_data.color);	// wall
	draw_line(data, data->draw_data.b, data->draw_data.floor, 0x3a333d);			// ground
	draw_line(data, data->draw_data.ceilling, data->draw_data.a, 0x88a6a2); 		// sky

	// printf("player vertical look : %i\n", data->player_vertical_look);

}
