/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:46 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/29 18:38:22 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int c, char const **v)
{

	t_data	data;

	data.FOV = 60;

	data.map = (char **)malloc(sizeof(char *) * 7);  // 7 map rows

	data.map_height = 7;
	data.map_width = 8;

	// MAP TEST
	data.map[0] = "11111111";
	data.map[1] = "10000001";
	data.map[2] = "10110001";
	data.map[3] = "10000S01"; // S for spawn
	data.map[4] = "10100001";
	data.map[5] = "10000101";
	data.map[6] = "11111111";

	raycast(&data);



	(void) c;
	(void) v;
	return 0;
}
