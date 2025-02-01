/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:49 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 17:12:30 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	minimise_point(t_data *data, t_2dpoint *point)
{
	point->x /= data->mini_scale;
	point->y /= data->mini_scale;

	point->x += data->mini_offset;
	point->y += data->mini_offset;
}

void	minimise_point_float(t_data *data, t_2dpoint_float *point)
{
	point->x /= (float) data->mini_scale;
	point->y /= (float) data->mini_scale;

	point->x += (float) data->mini_offset;
	point->y += (float) data->mini_offset;
}

t_2dpoint point_float_to_int(t_2dpoint_float point)
{
	return (make_point(((int)point.x), ((int)point.y)));
}
