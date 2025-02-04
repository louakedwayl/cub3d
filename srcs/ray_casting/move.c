/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:56:56 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:57:26 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// hooks mouse SIDE MOVEMENT ONLY
int	mouse_move_hook(int x, int y, t_data *data)
{
	static int	refresh_count;
	int			refresh_cooldown;

	refresh_cooldown = 1;
	if (data->key_hook_active == FALSE)
		return (0);
	look_horizontal(data, x);
	look_vertical(data, y);
	refresh_count++;
	if (refresh_count > refresh_cooldown)
		refresh_count = 0;
	else
		return (0);
	update_window(data);
	return (0);
}

void	move_azerty(t_data *data, int keycode)
{
	if (keycode == Z_KEY)
	{
		data->player_pos.x += data->delta_x;
		data->player_pos.y += data->delta_y;
	}
	else if (keycode == S_KEY)
	{
		data->player_pos.x -= data->delta_x;
		data->player_pos.y -= data->delta_y;
	}
	else if (keycode == Q_KEY)
	{
		data->player_pos.x -= data->side_delta_x;
		data->player_pos.y -= data->side_delta_y;
	}
	else if (keycode == D_KEY)
	{
		data->player_pos.x += data->side_delta_x;
		data->player_pos.y += data->side_delta_y;
	}
}

void	move_qwerty(t_data *data, int keycode)
{
	if (keycode == W_KEY)
	{
		data->player_pos.x += data->delta_x;
		data->player_pos.y += data->delta_y;
	}
	else if (keycode == S_KEY)
	{
		data->player_pos.x -= data->delta_x;
		data->player_pos.y -= data->delta_y;
	}
	else if (keycode == A_KEY)
	{
		data->player_pos.x -= data->side_delta_x;
		data->player_pos.y -= data->side_delta_y;
	}
	else if (keycode == D_KEY)
	{
		data->player_pos.x += data->side_delta_x;
		data->player_pos.y += data->side_delta_y;
	}
}

void	init_movement_vars(t_data *data)
{
	float		angle_radians;
	float		move_step_x;
	float		move_step_y;

	angle_radians = data->player_look_angle * (M_PI / 180.0);
	move_step_x = (WINDOW_WIDTH / 100);
	move_step_y = (WINDOW_HEIGHT / 100);
	data->delta_x = cos(angle_radians) * move_step_x;
	data->delta_y = sin(angle_radians) * move_step_y;
	data->side_delta_x = cos(angle_radians + M_PI_2) * move_step_x;
	data->side_delta_y = sin(angle_radians + M_PI_2) * move_step_y;
}

// Fonction pour appliquer les déplacements en fonction de l'angle de vue
void	move_player(t_data *data, int keycode)
{
	t_2dpoint	last_position;

	last_position = data->player_pos;
	init_movement_vars(data);
	if (KEYBOARD_TYPE == AZERTY)
		move_azerty(data, keycode);
	else if (KEYBOARD_TYPE == QWERTY)
		move_qwerty(data, keycode);
	data->player_pos.x = int_trunc(data->player_pos.x, 0, WINDOW_WIDTH);
	data->player_pos.y = int_trunc(data->player_pos.y, 0, WINDOW_HEIGHT);
	if (player_is_in_wall(data))
	{
		data->key_hook_active = FALSE;
		data->player_pos = last_position;
		update_window(data);
		return ;
	}
	update_window(data);
}
