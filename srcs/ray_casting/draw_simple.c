/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:41 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/31 04:01:14 by ajosse           ###   ########.fr       */
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






// function to rotate a point around center, by angle
t_2dpoint rotate_point(t_2dpoint point, t_2dpoint center, double angle)
{
	double radians = angle * (M_PI / 180.0);
	double cos_angle = cos(radians);
	double sin_angle = sin(radians);

	t_2dpoint rotated_point;
	rotated_point.x = cos_angle * (point.x - center.x) - sin_angle * (point.y - center.y) + center.x;
	rotated_point.y = sin_angle * (point.x - center.x) + cos_angle * (point.y - center.y) + center.y;

	return rotated_point;
}

void	draw_square_around_playerpos(t_data *data)
{
	// printf("player orientation : %i\n", data->player_look_angle);

	int size = 15;

	// Make corners
	t_2dpoint	top_left = make_point(data->player_pos.x - size, data->player_pos.y - size);
	t_2dpoint	top_right = make_point(data->player_pos.x + size, data->player_pos.y - size);
	t_2dpoint	bot_left = make_point(data->player_pos.x - size, data->player_pos.y + size);
	t_2dpoint	bot_right = make_point(data->player_pos.x + size, data->player_pos.y + size);

    // Apply rotation
    top_left = rotate_point(top_left, data->player_pos, data->player_look_angle);
    top_right = rotate_point(top_right, data->player_pos, data->player_look_angle);
    bot_left = rotate_point(bot_left, data->player_pos, data->player_look_angle);
    bot_right = rotate_point(bot_right, data->player_pos, data->player_look_angle);

	draw_white_square(data, top_left, top_right, bot_left, bot_right);
}


void	draw_square_around_point(t_data *data, t_2dpoint point)
{
	// printf("player orientation : %i\n", data->player_look_angle);

	int size = 44;

	// Make corners
	t_2dpoint	top_left = make_point(point.x - size, point.y - size);
	t_2dpoint	top_right = make_point(point.x + size, point.y - size);
	t_2dpoint	bot_left = make_point(point.x - size, point.y + size);
	t_2dpoint	bot_right = make_point(point.x + size, point.y + size);

	draw_white_square(data, top_left, top_right, bot_left, bot_right);
}










void	draw_red_square(t_data *data, t_2dpoint top_left, t_2dpoint top_right, t_2dpoint bot_left, t_2dpoint bot_right)
{
	int color = 0xc91c1c; //' red

	draw_line(data, top_left, top_right, color);
	draw_line(data, bot_left, bot_right, color);
	draw_line(data, top_left, bot_left, color);
	draw_line(data, top_right, bot_right, color);
}

void	draw_debug_red_square(t_data *data, t_2dpoint_float point)
{
	// printf("player orientation : %i\n", data->player_look_angle);

	int size = 2;

	// Make corners
	t_2dpoint	top_left = make_point((int) point.x - size, (int) point.y - size);
	t_2dpoint	top_right = make_point((int) point.x + size, (int) point.y - size);
	t_2dpoint	bot_left = make_point((int) point.x - size, (int) point.y + size);
	t_2dpoint	bot_right = make_point((int) point.x + size, (int) point.y + size);

	draw_red_square(data, top_left, top_right, bot_left, bot_right);
}
