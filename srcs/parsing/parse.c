/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:26:04 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:41:51 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_create_image(t_parsing_data *data)
{
	if (create_north(data))
		return (EXIT_FAILURE);
	if (create_south(data))
		return (EXIT_FAILURE);
	if (create_east(data))
		return (EXIT_FAILURE);
	if (create_west(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse(int argc, char **argv, t_parsing_data *data)
{
	init_data(data);
	if (handler_open_map(argc, argv, data))
		return (EXIT_FAILURE);
	if (set_data(data))
	{
		close(data->fd);
		free_data(data);
		return (EXIT_FAILURE);
	}
	if (ft_create_image(data))
	{
		if (data->img_north.img)
			mlx_destroy_image(data->mlx, data->img_north.img);
		if (data->img_south.img)
			mlx_destroy_image(data->mlx, data->img_south.img);
		if (data->img_east.img)
			mlx_destroy_image(data->mlx, data->img_east.img);
		if (data->img_west.img)
			mlx_destroy_image(data->mlx, data->img_west.img);
		close(data->fd);
		clear_map(data->map);
		return (EXIT_FAILURE);
	}
	close(data->fd);
	return (EXIT_SUCCESS);
}
