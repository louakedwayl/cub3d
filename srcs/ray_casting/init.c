/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:24:05 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 16:02:51 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_mlx_data	*init_mlx_data(t_data *data)
{
	t_mlx_data	*vars;

	vars = (t_mlx_data *) malloc(sizeof(t_mlx_data));
	if (!vars)
	{
		return (NULL);
	}
	vars->img = NULL;
	vars->win = NULL;
	vars->mlx = data->parsing_data->mlx;
	if (!vars->mlx)
	{
		free(vars);
		return (NULL);
	}
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->img)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!vars->win)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");
	return (vars);
}
