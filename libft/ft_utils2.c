/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:07:16 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/23 11:12:30 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*tab;
	int	i;

	if (min >= max)
		return (NULL);
	tab = malloc(sizeof(int) * (max - min));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i + min < max)
	{
		tab[i] = i + min;
		i++;
	}
	return (tab);
}

int	ft_factorial(int nb)
{
	int	a;

	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	a = nb;
	nb--;
	while (nb > 1)
	{
		a *= nb;
		nb--;
	}
	return (a);
}

int	ft_power(int nb, int power)
{
	int	a;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	a = 1;
	while (power > 0)
	{
		a *= nb;
		power--;
	}
	return (a);
}
