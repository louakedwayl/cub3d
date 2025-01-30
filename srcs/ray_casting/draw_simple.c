/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:41 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/30 14:25:46 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel_on_image(void *img, int x, int y, int color)
{
	char				*data;
	t_put_pixel_data	di;

	di.color = color;
	data = mlx_get_data_addr(img, &di.b_pixel, &di.size_line, &di.endian);
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	di.pixel_pos = (y * di.size_line) + (x * (di.b_pixel / 8));
	*(unsigned int *)(data + di.pixel_pos) = di.color;
}
