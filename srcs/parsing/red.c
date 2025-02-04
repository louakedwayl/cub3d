/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayl <wayl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:45:04 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/03 01:28:55 by wayl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char *ft_red(char *line)
{
    char *retstring;
    int i;
    int j;

    i = 2;
    j = 0;
    retstring = ft_calloc (sizeof(char), 1024);
    if (!retstring)
        return (NULL);
    while (line[i] && line[i] != ',' )
        retstring[j++] = line[i++];
    if (j == 0)
        return (NULL);
    return (retstring);
}

int set_red(char **line)
{
    int nbr;
    char *color;

    color = ft_red(*line);
    if (!color)
        return (-1);
    if (is_digit_string(color))
    {
        printf ("Error: floor RGB value must contain only digits.\n");
        ft_free(&color);
        return (-1);
    }
    nbr = ft_atoi(color);
    if (nbr > 255 || nbr < 0)
    {
        printf ("Error: Red must be between 0 and 255.\n");
        ft_free(&color);
        return (-1);
    }
    ft_free(&color);
    return (nbr);
}
