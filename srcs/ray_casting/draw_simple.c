/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:41 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 11:19:59 by ajosse           ###   ########.fr       */
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

	// printf("check x\n");

	// printf("data : %s, ", data);
	// printf("di.pixel_pos %i, ", di.pixel_pos);
	// printf("di.color %i\n", di.color);

	*(unsigned int *)(data + di.pixel_pos) = di.color;

	// printf("check y\n");
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
	put_pixel_on_image(data->mlx_data->img, b.x, b.y, color);
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

void	draw_map(t_data *data)
{
	t_2dpoint_float	square_center;
	t_2dpoint	point;
	int			index;
	int			row;

	index = 0;
	row = 0;

	while (row < data->map_height)
	{
		index = 0;
		while (index < data->map_width)
		{
			if (data->map[row][index] == '1')
			{
				square_center = make_float_point((float)index + 0.5f, (float)row + 0.5f);
				convert_map_coords_to_window_coords_float(data, &square_center);

				if (data->mode_mini)
				{
					minimise_point_float(data, &square_center);
				}

				point = point_float_to_int(square_center);
				if ((index != 0 && row != 0)
					&& (index != data->map_width - 1 && row != data->map_height - 1))
					draw_square_around_point(data, point);
			}
			index++;
		}
		row++;
	}
}
