/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:53 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/31 01:12:26 by ajosse           ###   ########.fr       */
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

    if (keycode == S_KEY)  // Backward
    {
        data->player_pos.x += delta_x;
        data->player_pos.y += delta_y;
    }
    if (keycode == Z_KEY)  // Forward
    {
        data->player_pos.x -= delta_x;
        data->player_pos.y -= delta_y;
    }
    if (keycode == D_KEY)  // Right
    {
        data->player_pos.x -= side_delta_x;
        data->player_pos.y -= side_delta_y;
    }
    if (keycode == Q_KEY)  // Left
    {
        data->player_pos.x += side_delta_x;
        data->player_pos.y += side_delta_y;
    }

    // Limiter la position pour qu'elle reste dans les bornes de la fenêtre
    data->player_pos.x = int_trunc(data->player_pos.x, 0, WINDOW_WIDTH);
    data->player_pos.y = int_trunc(data->player_pos.y, 0, WINDOW_HEIGHT);

    // Mettre à jour la fenêtre après le déplacement
    update_window(data);
}

// hooks
int	key_hook(int keycode, t_data *data)
{
	// if (DEBUG)
	// 	printf("%i pressed\n", keycode);

	if (keycode == ECHAP_KEY)
		esc_destroy_all(data);

	if (keycode == Z_KEY || keycode == Q_KEY || keycode == S_KEY || keycode == D_KEY)
		move_player(data, keycode);

	return (0);
}


// hooks mouse SIDE MOVEMENT ONLY
int	mouse_move_hook(int x, int y, t_data *data)
{
	static int last_x = 0;
	static int refresh_count;
	int refresh_limit = 5;
	int diff_x;

	diff_x = (x - last_x) / 5;

	data->player_look_angle += diff_x;

	if (data->player_look_angle >= 360)
		data->player_look_angle -= 360;
	else if (data->player_look_angle < 0)
		data->player_look_angle += 360;


	last_x = x;

	refresh_count++;
	if (refresh_count > refresh_limit)
		refresh_count = 0;
	else
		return (0);

	// printf("refreshing\n");

	update_window(data);
	(void) y;
	return (0);
}
