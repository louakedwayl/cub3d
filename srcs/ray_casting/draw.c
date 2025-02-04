/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:13:38 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:43:43 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// function to rotate a point around center, by angle
t_2dpoint	rotate_point(t_2dpoint point, t_2dpoint center, double angle)
{
	double		radians;
	double		cos_angle;
	double		sin_angle;
	t_2dpoint	rotated_point;

	radians = angle * (M_PI / 180.0);
	cos_angle = cos(radians);
	sin_angle = sin(radians);
	rotated_point.x = cos_angle * (point.x - center.x)
		- sin_angle * (point.y - center.y) + center.x;
	rotated_point.y = sin_angle * (point.x - center.x)
		+ cos_angle * (point.y - center.y) + center.y;
	return (rotated_point);
}

void	draw_square_around_playerpos(t_data *data)
{
	t_square_data	sd;
	int				size;

	size = 15;
	sd.top_left = make_point(data->player_pos.x
			- size, data->player_pos.y - size);
	sd.top_right = make_point(data->player_pos.x
			+ size, data->player_pos.y - size);
	sd.bot_left = make_point(data->player_pos.x
			- size, data->player_pos.y + size);
	sd.bot_right = make_point(data->player_pos.x
			+ size, data->player_pos.y + size);
	sd.top_left = rotate_point(sd.top_left,
			data->player_pos, data->player_look_angle);
	sd.top_right = rotate_point(sd.top_right,
			data->player_pos, data->player_look_angle);
	sd.bot_left = rotate_point(sd.bot_left,
			data->player_pos, data->player_look_angle);
	sd.bot_right = rotate_point(sd.bot_right,
			data->player_pos, data->player_look_angle);
	draw_white_square(data, &sd);
}

void	draw_square_around_point(t_data *data, t_2dpoint point)
{
	t_square_data	sd;
	int				size;

	size = (int) data->square_size / 2;
	if (data->mode_mini)
		size /= data->mini_scale;
	sd.top_left = make_point(point.x - size, point.y - size);
	sd.top_right = make_point(point.x + size, point.y - size);
	sd.bot_left = make_point(point.x - size, point.y + size);
	sd.bot_right = make_point(point.x + size, point.y + size);
	draw_white_square(data, &sd);
}

void	draw_colored_square(t_data *data, t_square_data *sd)
{
	draw_line(data, sd->top_left, sd->top_right, data->debug_color);
	draw_line(data, sd->bot_left, sd->bot_right, data->debug_color);
	draw_line(data, sd->top_left, sd->bot_left, data->debug_color);
	draw_line(data, sd->top_right, sd->bot_right, data->debug_color);
}

void	draw_debug_square(t_data *data, t_2dpoint_float point, int size)
{
	t_square_data	sd;

	sd.top_left = make_point((int) point.x - size, (int) point.y - size);
	sd.top_right = make_point((int) point.x + size, (int) point.y - size);
	sd.bot_left = make_point((int) point.x - size, (int) point.y + size);
	sd.bot_right = make_point((int) point.x + size, (int) point.y + size);
	if (data->mode_mini && !data->debug_mode)
	{
		minimise_point(data, &sd.top_left);
		minimise_point(data, &sd.top_right);
		minimise_point(data, &sd.bot_left);
		minimise_point(data, &sd.bot_right);
	}
	draw_colored_square(data, &sd);
}
