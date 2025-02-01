/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:53 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 16:34:49 by ajosse           ###   ########.fr       */
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
		if (data->map[on_map.y][on_map.x] == '1')
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

// Fonction pour appliquer les déplacements en fonction de l'angle de vue
void move_player(t_data *data, int keycode)
{
    float angle_radians = data->player_look_angle * (M_PI / 180.0);
    float move_step_x = (WINDOW_WIDTH / 100);
    float move_step_y = (WINDOW_HEIGHT / 100);

    // TOP / BOT WAYS
    float delta_x = cos(angle_radians) * move_step_x;
    float delta_y = sin(angle_radians) * move_step_y;

    // SIDEWAYS
    float side_delta_x = cos(angle_radians + M_PI_2) * move_step_x;  // perpendiculaire
    float side_delta_y = sin(angle_radians + M_PI_2) * move_step_y;  // 

	t_2dpoint last_position;
	last_position = data->player_pos;

	//, AZERTY
	if (keycode == Z_KEY && KEYBOARD_TYPE == AZERTY)  // Forward
	{
		data->player_pos.x += delta_x;
		data->player_pos.y += delta_y;
	}
	else if (keycode == S_KEY && KEYBOARD_TYPE == AZERTY)  // Backward
	{
		data->player_pos.x -= delta_x;
		data->player_pos.y -= delta_y;
	}
	else if (keycode == Q_KEY && KEYBOARD_TYPE == AZERTY)  // Left
	{
		data->player_pos.x -= side_delta_x;
		data->player_pos.y -= side_delta_y;
	}
	else if (keycode == D_KEY && KEYBOARD_TYPE == AZERTY)  // Right
	{
		data->player_pos.x += side_delta_x;
		data->player_pos.y += side_delta_y;
	}

	//, QWERTY
	if (keycode == W_KEY && KEYBOARD_TYPE == QWERTY)  // Forward
	{
		data->player_pos.x += delta_x;
		data->player_pos.y += delta_y;
	}
	else if (keycode == S_KEY && KEYBOARD_TYPE == QWERTY)  // Backward
	{
		data->player_pos.x -= delta_x;
		data->player_pos.y -= delta_y;
	}
	else if (keycode == A_KEY && KEYBOARD_TYPE == QWERTY)  // Left
	{
		data->player_pos.x -= side_delta_x;
		data->player_pos.y -= side_delta_y;
	}
	else if (keycode == D_KEY && KEYBOARD_TYPE == QWERTY)  // Right
	{
		data->player_pos.x += side_delta_x;
		data->player_pos.y += side_delta_y;
	}


    // Limiter la position pour qu'elle reste dans les bornes de la fenêtre
    data->player_pos.x = int_trunc(data->player_pos.x, 0, WINDOW_WIDTH);
    data->player_pos.y = int_trunc(data->player_pos.y, 0, WINDOW_HEIGHT);

	if (player_is_in_wall(data))
	{
		data->key_hook_active = FALSE;
		data->player_pos = last_position;
		update_window(data);
		return ;
	}

    // Mettre à jour la fenêtre après le déplacement
    update_window(data);
}

// hooks
int	key_hook(int keycode, t_data *data)
{
	if (data->key_hook_active == FALSE)
		return 0;

	// if (data->debug_mode)
	// printf("%i pressed\n", keycode);

	int diff_x;
	int diff_y;
	int sensi = 10;


	if (keycode == ECHAP_KEY)
		esc_destroy_all(data);

	else if (keycode == KEY_TAB)
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

	else if (keycode == Z_KEY || keycode == Q_KEY || keycode == S_KEY || keycode == D_KEY || keycode == W_KEY || keycode == A_KEY)
		move_player(data, keycode);

	else if (keycode == TOP_ARROW)
	{
		//, VERTICAL
		diff_y = -sensi;
		data->player_vertical_look += diff_y;
		if (data->player_vertical_look >= 90)
			data->player_vertical_look = 90;
		else if (data->player_vertical_look < -90)
			data->player_vertical_look = -90;
		data->last_y += -sensi;

		update_window(data);
	}

	else if (keycode == BOTTOM_ARROW)
	{
		//, VERTICAL
		diff_y = sensi;
		data->player_vertical_look += diff_y;
		if (data->player_vertical_look >= 90)
			data->player_vertical_look = 90;
		else if (data->player_vertical_look < -90)
			data->player_vertical_look = -90;
		data->last_y += sensi;

		update_window(data);
	}

	else if (keycode == LEFT_ARROW)
	{
		//, HORIZONTAL
		diff_x = -sensi;
		data->player_look_angle += diff_x;
		if (data->player_look_angle >= 360)
			data->player_look_angle -= 360;
		else if (data->player_look_angle < 0)
			data->player_look_angle += 360;
		data->last_x += -sensi;

		update_window(data);
	}

	else if (keycode == RIGHT_ARROW)
	{
		//, HORIZONTAL
		diff_x = sensi;
		data->player_look_angle += diff_x;
		if (data->player_look_angle >= 360)
			data->player_look_angle -= 360;
		else if (data->player_look_angle < 0)
			data->player_look_angle += 360;
		data->last_x += sensi;

		update_window(data);
	}

	return (0);
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
	int diff_x;
	diff_x = (x - data->last_x);
	data->player_look_angle += diff_x;
	if (data->player_look_angle >= 360)
		data->player_look_angle -= 360;
	else if (data->player_look_angle < 0)
		data->player_look_angle += 360;
	data->last_x = x;

	//, VERTICAL
	int diff_y;
	diff_y = (y - data->last_y);
	data->player_vertical_look += diff_y;
	if (data->player_vertical_look >= 90)
		data->player_vertical_look = 90;
	else if (data->player_vertical_look < -90)
		data->player_vertical_look = -90;
	data->last_y = y;

	// printf("b player_look_angle : %f\n", (float)data->player_look_angle);

	refresh_count++;
	if (refresh_count > refresh_cooldown)
		refresh_count = 0;
	else
		return (0);

	// printf("refreshing\n");

	update_window(data);
	(void) y;
	return (0);
}
