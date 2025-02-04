/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:07:55 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:08:36 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free(char **str)
{
	if (*str)
		free (*str);
	*str = NULL;
}

void	init_data(t_parsing_data *data)
{
	data->map = NULL;
	data->north = NULL;
	data->west = NULL;
	data->south = NULL;
	data->east = NULL;
	data->img_north.img = NULL;
	data->img_south.img = NULL;
	data->img_east.img = NULL;
	data->img_west.img = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
}

void	free_data(t_parsing_data *data)
{
	ft_free (&data->north);
	ft_free (&data->south);
	ft_free (&data->east);
	ft_free (&data->west);
}

int	is_digit_string(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
		{
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
