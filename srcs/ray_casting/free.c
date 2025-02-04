/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:38 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 15:46:02 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// free map[i] && free map
void	clear_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_mlx(t_data *data)
{
	if (data->parsing_data->img_north.img)
		mlx_destroy_image(data->mlx_data->mlx,
			data->parsing_data->img_north.img);
	if (data->parsing_data->img_south.img)
		mlx_destroy_image(data->mlx_data->mlx,
			data->parsing_data->img_south.img);
	if (data->parsing_data->img_east.img)
		mlx_destroy_image(data->mlx_data->mlx,
			data->parsing_data->img_east.img);
	if (data->parsing_data->img_west.img)
		mlx_destroy_image(data->mlx_data->mlx,
			data->parsing_data->img_west.img);
	if (data->mlx_data->img)
		mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);
	if (data->mlx_data->win)
		mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->win);
	mlx_destroy_display(data->mlx_data->mlx);
	free(data->mlx_data->mlx);
	free(data->mlx_data);
	data->mlx_data = NULL;
}

// free all (mlx vars included) and exit( exitcode )
void	free_all_and_exit(t_data *data, int exitcode, char *optional_msg)
{
	if (optional_msg != NULL)
		printf("Error: %s\n", optional_msg);
	if (data->mlx_data != NULL)
	{
		free_mlx(data);
	}
	ft_free(&data->parsing_data->east);
	ft_free(&data->parsing_data->west);
	ft_free(&data->parsing_data->north);
	ft_free(&data->parsing_data->south);
	clear_map(data->map);
	exit(exitcode);
}
