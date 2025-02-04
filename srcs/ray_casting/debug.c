/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:20:03 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:58:54 by ajosse           ###   ########.fr       */
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

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	return ;
}

void	toggle_debug_mode(t_data *data)
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
