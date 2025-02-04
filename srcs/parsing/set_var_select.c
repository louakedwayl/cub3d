/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:17:07 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/03 19:58:44 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int set_var_select(t_parsing_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
        if (set_no(data, &line))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
        if (set_we(data, &line))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
        if (set_so(data, &line))
			return (EXIT_FAILURE);
	}
    else if (!ft_strncmp(line, "EA ", 3))
	{
        if (set_ea(data, &line))
			return (EXIT_FAILURE);
	}
    return (EXIT_SUCCESS);
}


int set_var_select2(t_parsing_data *data, char *line)
{

    if (!ft_strncmp(line, "F ", 2))
	{
        if (set_floor(data, &line))
        {
            printf ("Error: parse error \n");
            return (EXIT_FAILURE);
        }
	}
    else if (!ft_strncmp(line, "C ", 2))
	{
        if (set_ceiling(data, &line))
        {
            printf ("Error: parse error\n");
            return (EXIT_FAILURE);
        }
	}
	else if (ft_strncmp(line, "NO ", 3)  && ft_strncmp(line, "SO ", 3)
         && ft_strncmp(line, "WE ", 3) && ft_strncmp(line, "EA ", 3))
	{
        printf ("%s\n", line);
            printf ("Error: parse error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int set_floor(t_parsing_data *data, char **line)
{

	if (!line || !*line || ft_strlen(*line) < 7)
	{
		ft_free(line);
		return (EXIT_FAILURE);
	}
    if (data->floor[0] == -1)
    {
        data->floor[0] = set_red(line);
        if (data->floor[0] == -1)
            return (EXIT_FAILURE);
        data->floor[1] = set_green(line);
        if (data->floor[1] == -1)
             return (EXIT_FAILURE);
        data->floor[2] = set_blue(line);
        if (data->floor[2] == -1)
             return (EXIT_FAILURE);
    }
    else
 		return (EXIT_FAILURE);
    if (data->floor[0] == -1 || data->floor[1] == -1 || data->floor[2] == -1 )
    {
        return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

int set_ceiling(t_parsing_data *data, char **line)
{

	if (!line || !*line || ft_strlen(*line) < 7)
	{
		ft_free(line);
		return (EXIT_FAILURE);
	}
    if (data->ceiling[0] == -1)
    {
        data->ceiling[0] = set_red(line);
        if (data->ceiling[0] == -1)
            return (EXIT_FAILURE);
        data->ceiling[1] = set_green(line);
        if (data->ceiling[1] == -1)
            return (EXIT_FAILURE);
        data->ceiling[2] = set_blue(line);
        if (data->ceiling[2] == -1)
            return (EXIT_FAILURE);
    }
    else
 		return (EXIT_FAILURE);
    if (data->ceiling[0] == -1 || data->ceiling[1] == -1 || data->ceiling[2] == -1 )
    {
        return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

