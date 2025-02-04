/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:56:26 by ajosse            #+#    #+#             */
/*   Updated: 2025/02/04 17:09:26 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// custom realloc
char	*ft_allocplus(char *buffer, size_t size)
{
	char	*new_buffer;
	size_t	n;

	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	n = ft_strlen(buffer);
	new_buffer = malloc(n + size + 1);
	if (!new_buffer)
		return (NULL);
	ft_memcpy(new_buffer, buffer, n);
	free(buffer);
	buffer = NULL;
	new_buffer[n] = '\0';
	return (new_buffer);
}

int	get_longest_line(char **map)
{
	int	longest_line;
	int	i;

	if (!map || !map[0])
		return (0);
	longest_line = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > longest_line)
			longest_line = (int)ft_strlen(map[i]);
		i++;
	}
	return (longest_line);
}

int	get_map_height(char **map)
{
	int	i;

	if (!map || !map[0])
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	fill_newmap(t_data *data, int i, int max, char **newmap)
{
	int		n;

	newmap[i] = (char *)calloc(max, sizeof(char *));
	if (!newmap[i])
	{
		clear_map(newmap);
		return ;
	}
	newmap[i][0] = '1';
	newmap[i][max] = '\0';
	if (i == 0 || i == max - 1)
		ft_memset(&newmap[i][1], '1', max - 1);
	else if (i - 1 < data->map_height)
	{
		ft_strlcpy(&(newmap[i][1]), data->map[i - 1],
			ft_strlen(data->map[i - 1]) + 1);
		n = ft_strlen(data->map[i - 1]) + 1;
		while (n < max)
		{
			newmap[i][n] = ' ';
			n++;
		}
	}
	else
		ft_memset(&newmap[i][1], ' ', max - 1);
	newmap[i][max - 1] = '1';
}

// make a '1' circle around the map to cover rays to path through
t_bool	transform_to_square_and_cover(t_data *data)
{
	char	**newmap;
	int		i;
	int		max;

	if (!data->map || !data->map[0])
		return (FALSE);
	if (data->map_height > data->map_width)
		max = data->map_height;
	else
		max = data->map_width;
	max += 2;
	newmap = (char **)ft_calloc(max + 1, sizeof(char *));
	if (!newmap)
		return (FALSE);
	i = 0;
	while (i < max)
	{
		fill_newmap(data, i, max, newmap);
		i++;
	}
	data->map_height = max;
	data->map_width = max;
	clear_map(data->map);
	data->map = newmap;
	return (TRUE);
}
