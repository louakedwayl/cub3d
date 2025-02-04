#include "../../includes/cub3d.h"

void	ft_free(char **str)
{
	if (*str)
		free (*str);
	*str = NULL;
}

void init_data(t_parsing_data *data)
{
	data->map = NULL;
	data->north = NULL;
	data->west = NULL;
	data->south = NULL;
	data->east = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
}

void free_data(t_parsing_data *data)
{
	ft_free (&data->north);
	ft_free (&data->south);
	ft_free (&data->east);
	ft_free (&data->west);
}

int	is_digit_string(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if(!ft_isdigit(string[i]))
		{
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
