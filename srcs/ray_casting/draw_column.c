/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:17:49 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 12:42:14 by ajosse           ###   ########.fr       */
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

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;
	int		color;

	// printf("getting pixel in ");
	// printf("(%i, %i)\n", x, y);
	// printf("adress : %s\n", texture->addr);

	pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));

	// printf("pixel : %s\n", pixel);

	color = *(unsigned int *)pixel;

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


	/// Transformer data->hit_part qui va de -data->square_size a data->square_size en 0-1

	// printf("hit_part : [%f]\n", data->hit_part);

	float normalized_hit_part = (data->hit_part + data->square_size) / (2.0f * data->square_size);

	//, 1 FIND X ON TEXTURE

	

	t_img	texture;

	if (data->wall_orientation == NORTH)
		texture = data->parsing_data->img_north;
	else if (data->wall_orientation == SOUTH)
		texture = data->parsing_data->img_south;
	else if (data->wall_orientation == EAST)
		texture = data->parsing_data->img_east;
	else
		texture = data->parsing_data->img_west;

	// printf("adrez : %s\n", texture.addr);;


	// data->hit_part; // TYPE int represente la partie du mur hit

	int texture_x = (int)(normalized_hit_part * texture.width);

	// printf("normalized : [%f], texture_x ; [%i]\n", normalized_hit_part, texture_x);

	if (texture_x < 0)
		texture_x = 0;
	if (texture_x >= texture.width)
		texture_x = texture.width - 1;

	

	//,2 GET COLOR AT POINT
	// int	get_texture_color(t_img *texture, int x, int y)


	//, 3 DRAW
	int line_height = data->draw_data.b.y - data->draw_data.a.y;

	int y = data->draw_data.a.y;

	int color;


	int diff;
	int	texture_y;


	int high = data->player_vertical_look * 5; // 5 full au pif wtf

	// printf("looking : %i\n", high);


	while (y < data->draw_data.b.y)
	{
		
		// Calcul Y in the texture
		diff = (y + high) * 256 - WINDOW_HEIGHT * 128 + line_height * 128;  // 256 et 128 texture scale
		texture_y = ((diff * texture.height) / line_height) / 256;

		if (texture_y < 0 || texture_y > texture.height)
		{
			y++;
			continue;
		}

		// printf("(%i, %i)\n", texture_x, texture_y);

		// Obtenir la couleur de la texture
		color = get_texture_color(&texture, texture_x, texture_y);

		// printf("1\n");

		// printf("column : [%i], y : [%i], color : [%i]\n", column, y, color);

		// Dessiner le pixel
		put_pixel_on_image(data->mlx_data->img, column, y, color);  // x est la colonne actuelle du rayon

		// printf("2\n");

		y++;
	}





	// data->draw_data.color = choose_color(data);

	// draw_line(data, data->draw_data.a, data->draw_data.b, data->draw_data.color);	// wall
	draw_line(data, data->draw_data.b, data->draw_data.floor, data->parsing_data->floor_color);			// ground
	draw_line(data, data->draw_data.ceilling, data->draw_data.a, data->parsing_data->ceil_color); 		// sky

	// printf("player vertical look : %i\n", data->player_vertical_look);

}
