/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:41 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:40:11 by ajosse           ###   ########.fr       */
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

void	bresenham_set(t_2dpoint a, t_2dpoint b, t_line_data *ld)
{
	ld->dx = abs(b.x - a.x);
	ld->dy = abs(b.y - a.y);
	if (a.x < b.x)
		ld->sx = 1;
	else
		ld->sx = -1;
	if (a.y < b.y)
		ld->sy = 1;
	else
		ld->sy = -1;
	ld->err = ld->dx - ld->dy;
}

// algorithme de Bresenham
void	draw_line(t_data *data, t_2dpoint a, t_2dpoint b, int color)
{
	t_line_data	ld;

	bresenham_set(a, b, &ld);
	while (a.x != b.x || a.y != b.y)
	{
		put_pixel_on_image(data->mlx_data->img, a.x, a.y, color);
		ld.e2 = 2 * ld.err;
		if (ld.e2 > -ld.dy)
		{
			ld.err -= ld.dy;
			a.x += ld.sx;
		}
		if (ld.e2 < ld.dx)
		{
			ld.err += ld.dx;
			a.y += ld.sy;
		}
	}
	put_pixel_on_image(data->mlx_data->img, b.x, b.y, color);
}

// for simple player representation
void	draw_white_square(t_data *data, t_square_data *sd)
{
	int	color;

	color = WHITE;
	draw_line(data, sd->top_left, sd->top_right, color);
	draw_line(data, sd->bot_left, sd->bot_right, color);
	draw_line(data, sd->top_left, sd->bot_left, color);
	draw_line(data, sd->top_right, sd->bot_right, color);
}
