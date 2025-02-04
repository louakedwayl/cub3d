/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_so.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:04:35 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:05:13 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_so(t_parsing_data *data, char **line)
{
	if (!line || !*line || ft_strlen(*line) < 4)
	{
		return (EXIT_FAILURE);
	}
	if (!data->south)
	{
		data->south = ft_substr(*line, 3, ft_strlen(*line) - 4);
		if (!data->south)
		{
			printf ("Error : set data->south \n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		printf ("Error : SO already set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
