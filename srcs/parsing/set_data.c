/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:41:27 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 17:18:03 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_norm_set_map(t_parsing_data *data, char **line)
{
	if (!*line || !*line[0])
	{
		printf ("Error: parse error\n");
		ft_free(line);
		return (EXIT_FAILURE);
	}
	while (ft_strncmp("\n", *line, 2) == 0)
	{
		ft_free (line);
		*line = get_next_line(data->fd);
		if (!*line)
		{
			printf ("Error: parse error\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_norm_set_map2(t_parsing_data *data, char **line, char **string)
{
	while (*line && *line[0])
	{
		*string = gnl_strjoin(*string, *line);
		if (!*line)
		{
			ft_free(&string);
			printf ("Error: parse error\n");
			return (EXIT_FAILURE);
		}
		free(*line);
		line = get_next_line(data->fd);
	}
	return (EXIT_SUCCESS);
}

int	set_map(t_parsing_data *data)
{
	int		i;
	char	*line;
	char	*string;
	char	**retstring;

	i = 0;
	string = NULL;
	line = get_next_line(data->fd);
	if (ft_norm_set_map(data, &line))
		return (EXIT_FAILURE);
	string = gnl_strjoin(string, line);
	free(line);
	line = get_next_line(data->fd);
	if (ft_norm_set_map2(data, &line, &string))
		return (EXIT_FAILURE);
	retstring = ft_split(string, '\n');
	if (!retstring)
	{
		ft_free(&string);
		printf ("Error: parse error\n");
		return (EXIT_FAILURE);
	}
	ft_free(&string);
	data->map = retstring;
	return (EXIT_SUCCESS);
}

int	set_data(t_parsing_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (set_var (data))
			return (EXIT_FAILURE);
		i++;
	}
	if (set_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_var(t_parsing_data *data)
{
	char	*line;

	line = get_next_line(data->fd);
	if (!line || !line[0])
	{
		printf ("Error: parse error\n");
		ft_free(&line);
		return (EXIT_FAILURE);
	}
	while (ft_strncmp("\n", line, 2) == 0)
	{
		ft_free (&line);
		line = get_next_line(data->fd);
		if (!line)
		{
			printf ("Error: parse error\n");
			return (EXIT_FAILURE);
		}
	}
	if (set_var_select(data, line))
		return (ft_free(&line), EXIT_FAILURE);
	if (set_var_select2(data, line))
		return (ft_free(&line), EXIT_FAILURE);
	ft_free(&line);
	return (EXIT_SUCCESS);
}
