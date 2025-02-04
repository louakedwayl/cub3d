/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blue.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:15:53 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:22:57 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_blue(char *line)
{
	char	*retstring;
	int		i;
	int		j;

	i = 2;
	j = 0;
	retstring = ft_calloc (sizeof(char), 1024);
	if (!retstring)
		return (NULL);
	while (line[i] && line[i] != ',' )
		i++;
	i++;
	while (line[i] && line[i] != ',' )
		i++;
	i++;
	while (line[i] && line[i] != '\n' )
		retstring[j++] = line[i++];
	return (retstring);
}

int	set_blue(char **line)
{
	int		nbr;
	char	*color;

	color = ft_blue(*line);
	if (!color)
		return (-1);
	if (is_digit_string(color))
	{
		ft_free(&color);
		return (-1);
	}
	nbr = ft_atoi(color);
	if (nbr > 255 || nbr < 0)
	{
		ft_free(&color);
		return (-1);
	}
	ft_free(&color);
	return (nbr);
}
