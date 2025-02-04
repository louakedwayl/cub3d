#include "../../includes/cub3d.h"

char *ft_green(char *line)
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
        i++;
    i++;
    while (line[i] && line[i] != ',' )
        retstring[j++] = line[i++];
    if (j == 0)
    {
        return (NULL);
    }
    return (retstring);
}

int set_green(char **line)
{
    int nbr;
    char *color;

    color = ft_green(*line);
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