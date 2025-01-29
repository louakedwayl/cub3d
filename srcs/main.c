
#include "../includes/cub3d.h"

int	ft_create_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		exit(EXIT_FAILURE);
	}
		data->mlx_win = mlx_new_window(data->mlx,
			WINDOW_WIDTH , WINDOW_HEIGHT, "cub3D");
	if (!data->mlx_win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int set_data_img(t_data *data)
{
	char	*line;
	//char	*string;
	//char	**retstring;

	line = get_next_line(data->fd);
	while (ft_strncmp("\n", line, 2) == 0)
	{
		free (line);
		line = get_next_line(data->fd);
	}
	printf ("%s", line);

	// while (line != NULL)
	// {
	// 	string = gnl_strjoin(string, line);
	// 	if (!string)
	// 		return (0);
	// 	free(line);
	// 	line = get_next_line(fd);
	// }
	// retstring = ft_split(string, '\n');
	// if (!retstring)
	// 	return (NULL);
	// return (close(fd), ft_free(&string), retstring);
	return (EXIT_SUCCESS);
}


int parse(int argc, char **argv, t_data *data)
{
	if (check_nbr_arg(argc))
		return (EXIT_FAILURE);
	if (check_name_map(argv))
		return (EXIT_FAILURE);
	if (open_map(data, argv[1]))
		return (EXIT_FAILURE);
	set_data_img(data);
		return (EXIT_FAILURE);
	close(data->fd);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data data;

	if(parse(argc, argv,&data))
		return (EXIT_FAILURE);
	ft_create_window(&data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
