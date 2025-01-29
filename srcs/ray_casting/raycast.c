
#include "../../includes/cub3d.h"

void	debug(void)
{
	printf("check\n");
}

// free map[i] && free map
void	clear_map(char **map)
{
	int	i;

	i = 0;
	// while (map[i])
	// {
	// 	free(map[i]);
	// }
	free(map);
}

// free all (mlx vars included) and exit( exitcode )
void	free_all_and_exit(t_data *data, int exitcode, char *optional_msg)
{
	if (optional_msg != NULL)
		printf("Error: %s\n", optional_msg);
	if (data->mlx_data != NULL)
	{
		if (data->mlx_data->img)
			mlx_destroy_image(data->mlx_data->mlx, data->mlx_data->img);
		if (data->mlx_data->win)
			mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->win);
		mlx_destroy_display(data->mlx_data->mlx);
		free(data->mlx_data->mlx);
		free(data->mlx_data);
	}
	clear_map(data->map);
	exit(exitcode);
}

t_mlx_data	*init_mlx_data(t_data *data)
{
	t_mlx_data	*vars;

	vars = (t_mlx_data *) malloc(sizeof(t_mlx_data));
	if (!vars)
	{
		return (NULL);
	}
	vars->img = NULL;
	vars->win = NULL;
	vars->mlx = NULL;
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		free(vars);
		return (NULL);
	}
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->img)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!vars->win)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");
	return (vars);
}

int	esc_destroy_all(t_data *data)
{
	free_all_and_exit(data, EXIT_SUCCESS, NULL);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		esc_destroy_all(data);
	return (0);
}

void	raycast(t_data *data)
{
	data->mlx_data = init_mlx_data(data);
	if (!data->mlx_data)
		free_all_and_exit(data, EXIT_FAILURE, "Failed to load mlx data");

	// CONSTRUIRE L'IMAGE

	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win, data->mlx_data->img, 0, 0);
	mlx_key_hook(data->mlx_data->win, key_hook, data->mlx_data);
	mlx_hook(data->mlx_data->win, 17, 0, esc_destroy_all, data);
	mlx_loop(data->mlx_data->mlx);

	free_all_and_exit(data, EXIT_SUCCESS, NULL);
}

// find . -type f | xargs cat | grep -a llebioda
