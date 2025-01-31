/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:38 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/30 23:03:16 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// free map[i] && free map
static void	clear_map(char **map)
{
	//int	i;

	//i = 0;
	// while (map[i])
	// {
	// 	free(map[i]);
	// }
	free(map);
}

// free all (mlx vars included) and exit( exitcode )
void	free_all_and_exit(t_data *data, int exitcode, char *optional_msg)
{
	if (optional_msg != NULL)
		printf("Error: %s\n", optional_msg);
	if (data->mlx_data != NULL)
	{
		if (data->mlx_data->img)
			mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);
		if (data->mlx_data->win)
			mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->win);
		mlx_destroy_display(data->mlx_data->mlx);
		free(data->mlx_data->mlx);
		free(data->mlx_data);
	}
	clear_map(data->map);
	exit(exitcode);
}
