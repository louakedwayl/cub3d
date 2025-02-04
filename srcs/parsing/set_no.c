/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_no.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:06:26 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:07:26 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_no(t_parsing_data *data, char **line)
{
	if (!line || !*line || ft_strlen(*line) < 4)
	{
		return (EXIT_FAILURE);
	}
	if (!data->north)
	{
		data->north = ft_substr(*line, 3, ft_strlen(*line) - 4);
		if (!data->north)
		{
			printf ("Error : set data->north \n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		printf ("Error : NO already set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
