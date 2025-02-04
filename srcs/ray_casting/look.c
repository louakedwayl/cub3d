/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:55:09 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:03:06 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	look_up(t_data *data, int sensi, int diff_y)
{
	diff_y = -sensi;
	data->player_vertical_look += diff_y;
	if (data->player_vertical_look >= 90)
		data->player_vertical_look = 90;
	else if (data->player_vertical_look < -90)
		data->player_vertical_look = -90;
	data->last_y += -sensi;
	update_window(data);
}

void	look_down(t_data *data, int sensi, int diff_y)
{
	diff_y = sensi;
	data->player_vertical_look += diff_y;
	if (data->player_vertical_look >= 90)
		data->player_vertical_look = 90;
	else if (data->player_vertical_look < -90)
		data->player_vertical_look = -90;
	data->last_y += sensi;
	update_window(data);
}

void	look_right(t_data *data, int sensi, int diff_x)
{
	diff_x = sensi;
	data->player_look_angle += diff_x;
	if (data->player_look_angle >= 360)
		data->player_look_angle -= 360;
	else if (data->player_look_angle < 0)
		data->player_look_angle += 360;
	data->last_x += sensi;
	update_window(data);
}

void	look_left(t_data *data, int sensi, int diff_x)
{
	diff_x = -sensi;
	data->player_look_angle += diff_x;
	if (data->player_look_angle >= 360)
		data->player_look_angle -= 360;
	else if (data->player_look_angle < 0)
		data->player_look_angle += 360;
	data->last_x += -sensi;
	update_window(data);
}

void	look_horizontal(t_data *data, int x)
{
	int	diff_x;

	diff_x = (x - data->last_x);
	data->player_look_angle += diff_x;
	if (data->player_look_angle >= 360)
		data->player_look_angle -= 360;
	else if (data->player_look_angle < 0)
		data->player_look_angle += 360;
	data->last_x = x;
}
