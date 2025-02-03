/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:53 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/03 04:09:21 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// trunc(999, 10, 100) = 100
int	int_trunc(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

float	float_trunc(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

// function called when hooked top right cross or echap
int	esc_destroy_all(t_data *data)
{
	free_all_and_exit(data, EXIT_SUCCESS, NULL);
	return (0);
}

t_bool	player_is_in_wall(t_data *data)
{
	t_2dpoint	on_map;

	on_map = make_point(data->player_pos.x, data->player_pos.y);
	convert_window_coords_to_map_coords(data, &on_map);

	if (data->map_height >= on_map.y && data->map_width >= on_map.x)
	{
		if (data->map[on_map.y][on_map.x] == '1' || data->map[on_map.y][on_map.x] == ' ')
		{
			return (TRUE);
		}
	}

	return (FALSE);
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
	data->side_delta_x = cos(angle_radians + M_PI_2) * move_step_x;  // perpendiculaire
	data->side_delta_y = sin(angle_radians + M_PI_2) * move_step_y;  // 
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

void	toggle_debug_mode(t_data *data)
{
	if (data->debug_mode)
	{
		printf("\033[1;31mDebug mode : OFF\033[m\n");
		data->debug_mode = FALSE;
	}
	else
	{
		printf("\033[1;31mDebug mode : ON\033[m\n");
		data->debug_mode = TRUE;
	}
	update_window(data);
}

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
		return 0;

	// if (data->debug_mode)
	// printf("%i pressed\n", keycode);

	if (keycode == ECHAP_KEY)
		esc_destroy_all(data);

	else if (keycode == KEY_TAB)
		toggle_debug_mode(data);

	else if (keycode == Z_KEY || keycode == Q_KEY || keycode == S_KEY || keycode == D_KEY || keycode == W_KEY || keycode == A_KEY)
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

void	look_vertical(t_data *data, int y)
{
	int diff_y;

	diff_y = (y - data->last_y);
	data->player_vertical_look += diff_y;
	if (data->player_vertical_look >= 90)
		data->player_vertical_look = 90;
	else if (data->player_vertical_look < -90)
		data->player_vertical_look = -90;
	data->last_y = y;
}

// hooks mouse SIDE MOVEMENT ONLY
int	mouse_move_hook(int x, int y, t_data *data)
{
	if (data->key_hook_active == FALSE)
		return 0;
	
	// printf("a player_look_angle : %f\n", (float)data->player_look_angle);

	// printf("x : %i\n", x);
	// printf("y : %i\n", y);

	// static int last_x = 0;
	// static int last_y = 0;

	static int refresh_count;
	int refresh_cooldown = 1; //. 1 mais UTILE flip/flop

	//, HORIZONTAL
	look_horizontal(data, x);

	//, VERTICAL
	look_vertical(data, y);

	// printf("b player_look_angle : %f\n", (float)data->player_look_angle);

	refresh_count++;
	if (refresh_count > refresh_cooldown)
		refresh_count = 0;
	else
		return (0);

	// printf("refreshing\n");

	update_window(data);
	return (0);
}
