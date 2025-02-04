/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:12:41 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 13:28:07 by ajosse           ###   ########.fr       */
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

	// data->mlx_win = mlx_new_window(data->mlx,
	// 	WINDOW_WIDTH , WINDOW_HEIGHT, "cub3D");

	// if (!data->mlx_win)
	// {
	// 	mlx_destroy_display(data->mlx);
	// 	free(data->mlx);
	// 	exit (EXIT_FAILURE);
	// }

	return (EXIT_SUCCESS);
}

int	make_color(int red, int green, int blue)
{
    return ((red << 16) | (green << 8) | blue);
}

int	main(int argc, char **argv)
{
	t_parsing_data data;

	ft_create_window(&data);

	if (parse(argc, argv,&data))
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}

	// printf ("data n-> %s \n", data.north);
	// printf ("data s-> %s \n", data.south);
	// printf ("data e-> %s \n", data.east);
	// printf ("data w-> %s \n", data.west);

	// printf ("ceiling[0] =%d , ceiling[1] =%d , ceiling[2] =%d\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);
	// printf ("floor[0] =%d , floor[1] =%d , floor[2] =%d\n", data.floor[0], data.floor[1], data.floor[2]);


	//start_game(NULL);
	
	//mlx_put_image_to_window(data.mlx, data.mlx_win, data.img_north.img , (0 * 0), (0 *0));
	//mlx_loop(data.mlx);

	data.floor_color = make_color(data.floor[0], data.floor[1], data.floor[2]);
	data.ceil_color = make_color(data.ceiling[0], data.ceiling[1], data.ceiling[2]);

	// mlx_destroy_display(data.mlx);
	// ft_free(data.mlx);
	// ft_free(data.mlx_win);

	// printf("PARSING DONE\n");

	start_game(&data);

	free_data(&data);
	return (EXIT_SUCCESS);
}
