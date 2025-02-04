/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:12:41 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 17:43:33 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_create_window(t_parsing_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error : mlx_init() a échoué\n");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	make_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	main(int argc, char **argv)
{
	t_parsing_data	data;

	ft_create_window(&data);
	if (parse(argc, argv, &data))
	{
		free_data(&data);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (EXIT_FAILURE);
	}
	data.floor_color = make_color(data.floor[0], data.floor[1], data.floor[2]);
	data.ceil_color = make_color(data.ceiling[0],
			data.ceiling[1], data.ceiling[2]);
	start_game(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
