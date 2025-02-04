/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:17:49 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:17:15 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	choose_color(t_data *data)
{
	int	color;

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

	pixel = texture->addr
		+ (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_colum_calculs(t_data *data, int column, float distance)
{
	data->draw_data.screen_height = WINDOW_HEIGHT;
	data->draw_data.view_distance = data->square_size;
	data->draw_data.column_height = ((float) data->draw_data.screen_height
			* data->draw_data.view_distance) / distance;
	data->draw_data.top = (data->draw_data.screen_height
			- (int)data->draw_data.column_height) / 2;
	data->draw_data.bottom = data->draw_data.top
		+ (int)data->draw_data.column_height;
	data->draw_data.a = make_point(column, data->draw_data.top);
	data->draw_data.b = make_point(column, data->draw_data.bottom);
	data->draw_data.ceilling = make_point(column, 0);
	data->draw_data.floor = make_point(column, WINDOW_HEIGHT);
	data->draw_data.a.y -= data->player_vertical_look * 5;
	data->draw_data.b.y -= data->player_vertical_look * 5;
}

void	setup_draw_vars(t_data *data, t_draw_data *dd)
{
	dd->normalized_hit_part = (data->hit_part + data->square_size)
		/ (2.0f * data->square_size);
	if (data->wall_orientation == NORTH)
		dd->texture = data->parsing_data->img_north;
	else if (data->wall_orientation == SOUTH)
		dd->texture = data->parsing_data->img_south;
	else if (data->wall_orientation == EAST)
		dd->texture = data->parsing_data->img_east;
	else
		dd->texture = data->parsing_data->img_west;
	dd->texture_x = (int)(dd->normalized_hit_part * dd->texture.width);
	if (dd->texture_x < 0)
		dd->texture_x = 0;
	if (dd->texture_x >= dd->texture.width)
		dd->texture_x = dd->texture.width - 1;
	dd->line_height = data->draw_data.b.y - data->draw_data.a.y;
	dd->y = data->draw_data.a.y;
	dd->high = data->player_vertical_look * 5;
}

// big distance = small column    because far
void	draw_pixel_column(t_data *data, int column, float distance)
{
	t_draw_data	dd;

	draw_colum_calculs(data, column, distance);
	setup_draw_vars(data, &dd);
	while (dd.y < data->draw_data.b.y)
	{
		dd.diff = (dd.y + dd. high) * 256
			- WINDOW_HEIGHT * 128 + dd.line_height * 128;
		dd.texture_y = ((dd.diff * dd.texture.height) / dd.line_height) / 256;
		if (dd.texture_y < 0 || dd.texture_y > dd.texture.height)
		{
			dd.y++;
			continue ;
		}
		dd.color = get_texture_color(&dd.texture, dd.texture_x, dd.texture_y);
		put_pixel_on_image(data->mlx_data->img, column, dd.y, dd.color);
		dd.y++;
	}
	draw_line(data, data->draw_data.b,
		data->draw_data.floor, data->parsing_data->floor_color);
	draw_line(data, data->draw_data.ceilling,
		data->draw_data.a, data->parsing_data->ceil_color);
}
