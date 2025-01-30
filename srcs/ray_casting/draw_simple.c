/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:41 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/30 15:06:04 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//' white = 0xffffff;
void	put_pixel_on_image(void *img, int x, int y, int color)
{
	char				*data;
	t_put_pixel_data	di;

	di.color = color;
	data = mlx_get_data_addr(img, &di.b_pixel, &di.size_line, &di.endian);
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	di.pixel_pos = (y * di.size_line) + (x * (di.b_pixel / 8));
	*(unsigned int *)(data + di.pixel_pos) = di.color;
}

// algorithme de Bresenham
void	draw_line(t_data *data, t_2dpoint a, t_2dpoint b, int color)
{
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	int sx = (a.x < b.x) ? 1 : -1;
	int sy = (a.y < b.y) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (a.x != b.x || a.y != b.y)
	{
		put_pixel_on_image(data->mlx_data->img, a.x, a.y, color);
		e2 = 2 * err;
		if (e2 > -dy) { err -= dy; a.x += sx; }
		if (e2 < dx) { err += dx; a.y += sy; }
	}
	put_pixel_on_image(data->mlx_data->img, b.x, b.y, color); // Assure que le dernier pixel est dessiné
}

// for simple player representation
void	draw_white_square(t_data *data, t_2dpoint top_left, t_2dpoint top_right, t_2dpoint bot_left, t_2dpoint bot_right)
{
	int color = 0xffffff; //' white

	draw_line(data, top_left, top_right, color);
	draw_line(data, bot_left, bot_right, color);
	draw_line(data, top_left, bot_left, color);
	draw_line(data, top_right, bot_right, color);
}

void	draw_square_around_playerpos(t_data *data)
{
	t_2dpoint	top_left = make_point(data->player_pos.x - 20, data->player_pos.y - 20);
	t_2dpoint	top_right = make_point(data->player_pos.x + 20, data->player_pos.y - 20);
	t_2dpoint	bot_left = make_point(data->player_pos.x - 20, data->player_pos.y + 20);
	t_2dpoint	bot_right = make_point(data->player_pos.x + 20, data->player_pos.y + 20);

	draw_white_square(data, top_left, top_right, bot_left, bot_right);
}
