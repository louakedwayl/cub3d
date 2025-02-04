/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:41:27 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 11:55:39 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int set_map(t_parsing_data *data)
{
	int		i;
	char	*line;
	char	*string;

	string = NULL; //* new
	//	char	**retstring;

	i = 0;
	line = get_next_line(data->fd);
	if (!line || !line[0] )
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
	line = get_next_line(data->fd);
	// printf ("%s\n", line);
	while (line && line[0] && line[0] != '\n')
	{
		// printf("trying to join : [%s] and [%s]\n", string, line);
		string = gnl_strjoin(string, line);
		if (!line)
	 		return (EXIT_FAILURE);
	 	free(line);	
	 	line = get_next_line(data->fd);
	}

	//! Attention il manque la premiere ligne de la map

	// printf ("%s", string);

	// retstring = ft_split(string, '\n');
	// if (!retstring)
	// 	return (EXIT_FAILURE);
	// printf ("retstring[i] = %s", retstring[i]);
	return (EXIT_SUCCESS);
}

int set_data(t_parsing_data *data)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if( set_var (data))
            return (EXIT_FAILURE);
        i++;
    }
	if ( set_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int set_var(t_parsing_data *data)
{
	char	*line;

	line = get_next_line(data->fd);
	if (!line || !line[0] )
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
	return (EXIT_SUCCESS);
}

