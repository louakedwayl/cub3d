/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:19:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:38:52 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	trace_and_display(t_data *data, float start_angle, float end_angle)
{
	int		column;
	float	distance;

	column = 0;
	data->mode_mini = TRUE;
	while (start_angle < end_angle)
	{
		distance = process_raycasting(data, start_angle);
		if (!data->debug_mode)
			if (distance > 4.0f)
				draw_pixel_column(data, column, distance);
		column++;
		start_angle += 1.0f / ((float)WINDOW_WIDTH / (float)data->FOV);
	}
	data->mode_mini = FALSE;
}

void	update_window(t_data *data)
{
	float	start_angle;
	float	end_angle;

	if (data->mlx_data->img)
		mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);
	data->mlx_data->img = mlx_new_image(data->mlx_data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	start_angle = (float)((float)data->player_look_angle
			- (float)data->FOV / 2.0f);
	end_angle = (float)((float)data->player_look_angle
			+ (float)data->FOV / 2.0f);
	trace_and_display(data, start_angle, end_angle);
	if (data->debug_mode)
		draw_map(data);
	if (!data->debug_mode)
	{
		data->mode_mini = TRUE;
		draw_map(data);
		data->mode_mini = FALSE;
	}
	mlx_put_image_to_window(data->mlx_data->mlx,
		data->mlx_data->win, data->mlx_data->img, 0, 0);
	data->key_hook_active = TRUE;
}
