/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:32:37 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:41:26 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_north(t_parsing_data *data)
{
	data->img_north.img = mlx_xpm_file_to_image(data->mlx, data->north,
			&(data->img_north.width), &(data->img_north.height));
	if (!data->img_north.img)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->north);
		return (EXIT_FAILURE);
	}
	data->img_north.addr = mlx_get_data_addr(data->img_north.img,
			&(data->img_north.bits_per_pixel),
			&(data->img_north.line_length), &(data->img_north.endian));
	if (!data->img_north.addr)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->north);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_south(t_parsing_data *data)
{
	data->img_south.img = mlx_xpm_file_to_image(data->mlx, data->south,
			&(data->img_south.width), &(data->img_south.height));
	if (!data->img_south.img)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->south);
		return (EXIT_FAILURE);
	}
	data->img_south.addr = mlx_get_data_addr(data->img_south.img,
			&(data->img_south.bits_per_pixel),
			&(data->img_south.line_length), &(data->img_south.endian));
	if (!data->img_south.addr)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->south);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_east(t_parsing_data *data)
{
	data->img_east.img = mlx_xpm_file_to_image(data->mlx, data->east,
			&(data->img_east.width), &(data->img_east.height));
	if (!data->img_east.img)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->east);
		return (EXIT_FAILURE);
	}
	data->img_east.addr = mlx_get_data_addr(data->img_east.img,
			&(data->img_east.bits_per_pixel),
			&(data->img_east.line_length), &(data->img_east.endian));
	if (!data->img_east.addr)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->east);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_west(t_parsing_data *data)
{
	data->img_west.img = mlx_xpm_file_to_image(data->mlx, data->west,
			&(data->img_west.width), &(data->img_west.height));
	if (!data->img_west.img)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->west);
		return (EXIT_FAILURE);
	}
	data->img_west.addr = mlx_get_data_addr(data->img_west.img,
			&(data->img_west.bits_per_pixel), &(data->img_west.line_length),
			&(data->img_west.endian));
	if (!data->img_west.addr)
	{
		printf("Erreur : Impossible de charger l image %s\n", data->west);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
