/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:23:20 by wlouaked          #+#    #+#             */
/*   Updated: 2025/02/04 16:23:58 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_nbr_arg(int argc)
{
	if (argc < 2)
	{
		printf ("Error :Please select a map\n");
		return (EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf ("Error :Too much arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_name_map(char **argv)
{
	int	i;

	i = ft_strlen (argv[1]) - 1;
	if (argv[1][i--] != 'b')
		return (printf ("Error :Incorrect name maps\n"),
			(EXIT_FAILURE));
	else if (argv[1][i--] != 'u')
		return (printf ("Error :Incorrect name maps\n"),
			(EXIT_FAILURE));
	else if (argv[1][i--] != 'c')
		return (printf ("Error :Incorrect name maps\n"),
			(EXIT_FAILURE));
	else if (argv[1][i--] != '.')
		return (printf ("Error :Incorrect name maps\n"),
			(EXIT_FAILURE));
	else if (!argv[1][i])
		return (printf ("Error :Incorrect name maps\n"),
			(EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	open_map(t_parsing_data *data, char *map)
{
	data->fd = open(map, O_RDONLY);
	if (data->fd == -1)
	{
		printf ("Error :File unknown.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	handler_open_map(int argc, char **argv, t_parsing_data *data)
{
	if (check_nbr_arg(argc))
		return (EXIT_FAILURE);
	if (check_name_map(argv))
		return (EXIT_FAILURE);
	if (open_map(data, argv[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
