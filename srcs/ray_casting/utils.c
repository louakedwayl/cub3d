/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:52:35 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/30 14:54:43 by ajosse           ###   ########.fr       */
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
