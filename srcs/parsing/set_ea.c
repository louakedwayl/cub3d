#include "../../includes/cub3d.h"

int set_ea(t_parsing_data *data, char **line)
{
	if (!line || !*line || ft_strlen(*line) < 4)
	{
		return (EXIT_FAILURE);
	}
	if (!data->east)
	{
		data->east = ft_substr(*line, 3 , ft_strlen(*line) - 4);
		if (!data->east)
		{
			printf ("Error : set data->east \n");
			return (EXIT_FAILURE);
		}
	}
	else 
	{
		printf ("Error : EA already set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}