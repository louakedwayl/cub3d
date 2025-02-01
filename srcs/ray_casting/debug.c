/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:20:03 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/01 17:54:02 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_point(t_2dpoint point)
{
	printf("(%i, %i)\n", point.x, point.y);
}

void	print_point_float(t_2dpoint_float point)
{
	printf("(%f, %f)\n", point.x, point.y);
}
