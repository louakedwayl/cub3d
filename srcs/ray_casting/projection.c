/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:30:32 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:36:31 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_raydata(t_data *data,
	float angle, t_ray_data *rd, t_2dpoint_float *ray)
{
	rd->angle_rad = angle * (M_PI / 180.0f);
	rd->dx = (float) cos(rd->angle_rad);
	rd->dy = (float) sin(rd->angle_rad);
	rd->on_map = make_float_point(ray->x, ray->y);
	convert_window_coords_to_map_coords_float(data, &rd->on_map);
	rd->temp = point_float_to_int(rd->on_map);
	convert_map_coords_to_window_coords(data, &rd->temp);
	rd->on_map = make_float_point((float)rd->temp.x, (float)rd->temp.y);
	rd->on_map.x += (float) data->square_size / 2.0f;
	rd->on_map.y += (float) data->square_size / 2.0f;
	rd->on_map_cpy = make_float_point(rd->on_map.x, rd->on_map.y);
	rd->point_x_projection = make_float_point(-1000, -1000);
	rd->point_y_projection = make_float_point(-1000, -1000);
	rd->hit_part_side = 0.0f;
	rd->hit_part_vertical = 0.0f;
}

void	project_ray_horizontal(t_data *data,
	t_2dpoint_float *ray, t_ray_data *rd)
{
	if (rd->dx > 0)
		rd->on_map.x += data->square_size / 2.0f;
	else
		rd->on_map.x -= data->square_size / 2.0f;
	rd->temp_map_coord = rd->on_map.y;
	rd->on_map.y = ray->y;
	rd->distance = fabs((rd->on_map.x - ray->x) / rd->dx);
	rd->point_x_projection.x = ray->x + (rd->dx * rd->distance);
	rd->point_x_projection.y = ray->y + (rd->dy * rd->distance);
	rd->hit_part_side = (rd->point_x_projection.y - rd->temp_map_coord);
}

void	project_ray_vertical(t_data *data, t_2dpoint_float *ray, t_ray_data *rd)
{
	if (rd->dy < 0)
		rd->on_map_cpy.y -= data->square_size / 2.0f;
	else
		rd->on_map_cpy.y += data->square_size / 2.0f;
	rd->temp_map_coord = rd->on_map.x;
	rd->on_map_cpy.x = ray->x;
	rd->distance = fabs((rd->on_map_cpy.y - ray->y) / rd->dy);
	rd->point_y_projection.x = ray->x + (rd->dx * rd->distance);
	rd->point_y_projection.y = ray->y + (rd->dy * rd->distance);
	rd->hit_part_vertical = (rd->point_y_projection.x - rd->temp_map_coord);
}
