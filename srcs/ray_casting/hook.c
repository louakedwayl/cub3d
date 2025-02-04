/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:53 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:59:52 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// trunc(999, 10, 100) = 100
int	int_trunc(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	float_trunc(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_bool	player_is_in_wall(t_data *data)
{
	t_2dpoint	on_map;

	on_map = make_point(data->player_pos.x, data->player_pos.y);
	convert_window_coords_to_map_coords(data, &on_map);
	if (data->map_height >= on_map.y && data->map_width >= on_map.x)
	{
		if (data->map[on_map.y][on_map.x] == '1'
			|| data->map[on_map.y][on_map.x] == ' ')
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

// hooks
int	key_hook(int keycode, t_data *data)
{
	int	diff_x;
	int	diff_y;
	int	sensi;

	diff_x = 0;
	diff_y = 0;
	sensi = 10;
	if (data->key_hook_active == FALSE)
		return (0);
	if (keycode == ECHAP_KEY)
		esc_destroy_all(data);
	else if (keycode == KEY_TAB)
		toggle_debug_mode(data);
	else if (keycode == Z_KEY || keycode == Q_KEY || keycode == S_KEY
		|| keycode == D_KEY || keycode == W_KEY || keycode == A_KEY)
		move_player(data, keycode);
	else if (keycode == TOP_ARROW)
		look_up(data, sensi, diff_y);
	else if (keycode == BOTTOM_ARROW)
		look_down(data, sensi, diff_y);
	else if (keycode == LEFT_ARROW)
		look_left(data, sensi, diff_x);
	else if (keycode == RIGHT_ARROW)
		look_right(data, sensi, diff_x);
	return (0);
}

void	look_vertical(t_data *data, int y)
{
	int	diff_y;

	diff_y = (y - data->last_y);
	data->player_vertical_look += diff_y;
	if (data->player_vertical_look >= 90)
		data->player_vertical_look = 90;
	else if (data->player_vertical_look < -90)
		data->player_vertical_look = -90;
	data->last_y = y;
}
