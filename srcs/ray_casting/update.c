/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:19:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/02 19:30:37 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	trace_and_display(t_data *data, float start_angle, float end_angle)
{
	int	column;
	int	distance;

	column = 0;
	data->mode_mini = TRUE;
	while (start_angle < end_angle)
	{
		distance = process_raycasting(data, start_angle);

		// printf("distance : %i\n", distance);

		if (!data->debug_mode)
			if (distance > 4)
				draw_pixel_column(data, column, distance); //, DRAW

		column++;
		
		// printf("start_angle : %f\n", start_angle);

		start_angle += 1.0f / ((float)WINDOW_WIDTH / (float)data->FOV);
	}
	data->mode_mini = FALSE;
}

void	update_window(t_data *data)
{
	float start_angle;
	float end_angle;

	if (data->mlx_data->img)
		mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);

	data->mlx_data->img = mlx_new_image(data->mlx_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	start_angle = (float) ((float)data->player_look_angle - (float)data->FOV / 2.0f);
	end_angle = (float) ((float)data->player_look_angle + (float)data->FOV / 2.0f);

	// printf("x player_look_angle : %f\n", (float)data->player_look_angle);
	// printf("FOV : %f\n", (float)data->FOV);

	// printf("start_angle : %f\n", start_angle);
	// printf("end_angle : %f\n", end_angle);
	// printf("\n");

	// int range = (int) start_angle - (int) end_angle;

	trace_and_display(data, start_angle, end_angle);

	// draw_square_around_playerpos(data);

	if (data->debug_mode)
		draw_map(data); // j'aimerais éviter de le faire à chaque fois vu que c'est fixe

	if (!data->debug_mode)
	{
		data->mode_mini = TRUE;
		draw_map(data);
		data->mode_mini = FALSE;
	}

	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win, data->mlx_data->img, 0, 0);
	
	data->key_hook_active = TRUE;

	
	// sleep(0.01);

	// usleep(1000);
}
