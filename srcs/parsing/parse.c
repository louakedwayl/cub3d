#include "../../includes/cub3d.h"

int    ft_create_image(t_parsing_data *data)
{
    // int        nbr;
    // char    *path;

    // path = ft_strjoin("./textures/", data->north); //! jsp si c est good
    // printf("%s\n", data->north);

    // nbr = 0;
    //. NORTH
    data->img_north.img = mlx_xpm_file_to_image(data->mlx, data->north , &(data->img_north.width), &(data->img_north.height));
    if (!data->img_north.img)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->north);
        return (EXIT_FAILURE);
    }
    data->img_north.addr = mlx_get_data_addr(data->img_north.img, &(data->img_north.bits_per_pixel), &(data->img_north.line_length), &(data->img_north.endian));
    if (!data->img_north.addr)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->north);
        return (EXIT_FAILURE);
    }

    //. SOUTH
    data->img_south.img = mlx_xpm_file_to_image(data->mlx, data->south , &(data->img_south.width), &(data->img_south.height));
    if (!data->img_south.img)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->south);
        return (EXIT_FAILURE);
    }
    data->img_south.addr = mlx_get_data_addr(data->img_south.img, &(data->img_south.bits_per_pixel), &(data->img_south.line_length), &(data->img_south.endian));
    if (!data->img_south.addr)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->south);
        return (EXIT_FAILURE);
    }

    //. EAST
    data->img_east.img = mlx_xpm_file_to_image(data->mlx, data->east , &(data->img_east.width), &(data->img_east.height));
    if (!data->img_east.img)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->east);
        return (EXIT_FAILURE);
    }
    data->img_east.addr = mlx_get_data_addr(data->img_east.img, &(data->img_east.bits_per_pixel), &(data->img_east.line_length), &(data->img_east.endian));
    if (!data->img_east.addr)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->east);
        return (EXIT_FAILURE);
    }

    //. WEST
    data->img_west.img = mlx_xpm_file_to_image(data->mlx, data->west , &(data->img_west.width), &(data->img_west.height));
    if (!data->img_west.img)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->west);
        return (EXIT_FAILURE);
    }
    data->img_west.addr = mlx_get_data_addr(data->img_west.img, &(data->img_west.bits_per_pixel), &(data->img_west.line_length), &(data->img_west.endian));
    if (!data->img_west.addr)
    {
        perror("mlx_xpm_file_to_image");
        printf("Erreur : Impossible de charger l’image %s\n", data->west);
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

int parse(int argc, char **argv, t_parsing_data *data)
{
	init_data(data);
	if (handler_open_map(argc, argv, data))
		return (EXIT_FAILURE);
	if (set_data(data))
	{
		free_data(data);
		return (EXIT_FAILURE);
	}
	if (ft_create_image(data))
		return (EXIT_FAILURE);
	close(data->fd);
	return (EXIT_SUCCESS);
}



