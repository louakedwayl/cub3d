/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:26:43 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:30:21 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_ray_horizontal(t_data *data, t_2dpoint_float *ray, t_ray_data *rd)
{
	data->hit_part = rd->hit_part_side;
	ray->x = rd->point_x_projection.x;
	ray->y = rd->point_x_projection.y;
	if (rd->dx > 0)
	{
		data->wall_orientation = EAST;
		data->debug_color = 0x00ccff;
	}
	else
	{
		data->wall_orientation = WEST;
		data->debug_color = 0xffff00;
	}
}

void	set_ray_vertical(t_data *data,
	t_2dpoint_float *ray, t_ray_data *rd)
{
	data->hit_part = rd->hit_part_vertical;
	ray->x = rd->point_y_projection.x;
	ray->y = rd->point_y_projection.y;
	if (rd->dy > 0)
	{
		data->wall_orientation = SOUTH;
		data->debug_color = 0x9900ff;
	}
	else
	{
		data->wall_orientation = NORTH;
		data->debug_color = 0xffffff;
	}
}

void	update_ray(t_data *data, float cast_angle)
{
	if (data->debug_mode)
	{
		data->debug_color = 0xc91c1c;
		draw_debug_square(data, data->rc.ray, 2);
	}
	if (data->mode_mini && data->rc.print_limit_count
		== data->rc.debug_print_limit)
	{
		data->debug_color = 0xc91c1c;
		draw_debug_square(data, data->rc.ray, 1);
	}
	forward_ray(data, &data->rc.ray, cast_angle);
}

void	init_raycast_vars(t_data *data)
{
	data->rc.print_limit_count++;
	if (data->rc.print_limit_count > data->rc.debug_print_limit)
	{
		data->rc.print_limit_count = 0;
	}
	else
		data->rc.print_limit_count++;
	data->rc.x = (float)data->player_pos.x;
	data->rc.y = (float)data->player_pos.y;
	data->rc.ray = make_float_point(data->rc.x, data->rc.y);
	data->rc.i = 0;
}

void	forward_ray(t_data *data, t_2dpoint_float *ray, float angle)
{
	t_ray_data	rd;

	init_raydata(data, angle, &rd, ray);
	if (rd.dx != 0)
		project_ray_horizontal(data, ray, &rd);
	if (rd.dy != 0)
		project_ray_vertical(data, ray, &rd);
	if (get_distance_float((*ray), rd.point_x_projection)
		< get_distance_float((*ray), rd.point_y_projection))
		set_ray_horizontal(data, ray, &rd);
	else
		set_ray_vertical(data, ray, &rd);
	if (rd.dx > 0)
		ray->x += 0.01f;
	else
		ray->x -= 0.01f;
	if (rd.dy > 0)
		ray->y += 0.01f;
	else
		ray->y -= 0.01f;
	data->rc.ray = *ray;
	data->rc.hit_point = data->rc.ray;
}
