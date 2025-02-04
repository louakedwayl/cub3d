/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_we.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:03:17 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:04:04 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_we(t_parsing_data *data, char **line)
{
	if (!line || !*line || ft_strlen(*line) < 4)
	{
		return (EXIT_FAILURE);
	}
	if (!data->west)
	{
		data->west = ft_substr(*line, 3, ft_strlen(*line) - 4);
		if (!data->west)
		{
			printf ("Error : set data->west \n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		printf ("Error : WE already set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
