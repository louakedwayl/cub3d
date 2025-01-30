/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:18:53 by ajosse            #+#    #+#             */
/*   Updated: 2025/01/30 15:10:15 by ajosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// function called when hooked top right cross or echap
int	esc_destroy_all(t_data *data)
{
	free_all_and_exit(data, EXIT_SUCCESS, NULL);
	return (0);
}

// All hooks
int	key_hook(int keycode, t_data *data)
{
	if (DEBUG)
		printf("%i pressed\n", keycode);

	if (keycode == 65307)
		esc_destroy_all(data);

	// FAIRE KEY HOLDING. RELEASE
	// avec des t_bool

	return (0);
}

// 65362 pressed haut
// 65364 pressed bas
// 65361 pressed gauche
// 65363 pressed droite