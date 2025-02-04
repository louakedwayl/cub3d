/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:52:35 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:40:28 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// return a t_2dpoint with coor (x, y)
t_2dpoint	make_point(int x_value, int y_value)
{
	t_2dpoint	new;

	new.x = x_value;
	new.y = y_value;
	return (new);
}

// return a t_2dpoint_float with coor (x, y)
t_2dpoint_float	make_float_point(float x_value, float y_value)
{
	t_2dpoint_float	new;

	new.x = x_value;
	new.y = y_value;
	return (new);
}

float	get_distance(t_2dpoint a, t_2dpoint b)
{
	int	dx;
	int	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return ((float)sqrt(dx * dx + dy * dy));
}

float	get_distance_float(t_2dpoint_float a, t_2dpoint_float b)
{
	float	dx;
	float	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrtf(dx * dx + dy * dy));
}
