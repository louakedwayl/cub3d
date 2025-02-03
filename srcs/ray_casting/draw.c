/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:13:38 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/02 23:40:27 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

	int size = (int) data->square_size / 2;

	if (data->mode_mini)
		size /= data->mini_scale;

	// Make corners
	t_2dpoint	top_left = make_point(point.x - size, point.y - size);
	t_2dpoint	top_right = make_point(point.x + size, point.y - size);
	t_2dpoint	bot_left = make_point(point.x - size, point.y + size);
	t_2dpoint	bot_right = make_point(point.x + size, point.y + size);

	draw_white_square(data, top_left, top_right, bot_left, bot_right);
}

void	draw_colored_square(t_data *data, t_2dpoint top_left, t_2dpoint top_right, t_2dpoint bot_left, t_2dpoint bot_right)
{
	draw_line(data, top_left, top_right, data->debug_color);
	draw_line(data, bot_left, bot_right, data->debug_color);
	draw_line(data, top_left, bot_left, data->debug_color);
	draw_line(data, top_right, bot_right, data->debug_color);
}

void	draw_debug_square(t_data *data, t_2dpoint_float point, int size)
{
	// printf("player orientation : %i\n", data->player_look_angle);

	// printf("ray : ");
	// print_point_float(point);

	// Make corners
	t_2dpoint	top_left = make_point((int) point.x - size, (int) point.y - size);
	t_2dpoint	top_right = make_point((int) point.x + size, (int) point.y - size);
	t_2dpoint	bot_left = make_point((int) point.x - size, (int) point.y + size);
	t_2dpoint	bot_right = make_point((int) point.x + size, (int) point.y + size);

	// print_point(top_left);
	// print_point(top_right);
	// print_point(bot_left);
	// print_point(bot_right);

	if (data->mode_mini && !data->debug_mode)
	{
		minimise_point(data, &top_left);
		minimise_point(data, &top_right);
		minimise_point(data, &bot_left);
		minimise_point(data, &bot_right);
	}

	draw_colored_square(data, top_left, top_right, bot_left, bot_right);
}
