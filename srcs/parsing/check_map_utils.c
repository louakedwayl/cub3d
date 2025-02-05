/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:19:26 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/05 17:25:35 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char **ft_strrdup(char **s)
{
	char	**rettab;
	int	i;

	i = 0;
	while (s[i])
		i++;
	rettab = ft_calloc (sizeof(char*) ,(i +1));
	if (!rettab)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rettab[i] = ft_strdup(s[i]);
		if (!rettab[i])
		{
			clear_map(rettab);
			return (NULL);
		}
		i++;
	}
	return (rettab);
}

void printf_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
}

void	ft_set_xmax(t_parsing_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			j++;
		}
		if (j > data->xmax)
			data->xmax = j;
		i++;
	}
}

void	ft_set_ymax(t_parsing_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		i++;
	}
	data->ymax = i;
}
