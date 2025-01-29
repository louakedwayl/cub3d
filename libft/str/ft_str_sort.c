/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:10 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/09 16:54:21 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_str(char **tab)
{
	ft_custom_sort_str(tab, &ft_strcmp);
}

void	ft_custom_sort_str(char **tab, int (*cmp)(const char *, const char *))
{
	char	*temp;
	int		i;
	int		j;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
		i++;
	if (i <= 1)
		return ;
	while (i-- > 1)
	{
		j = 0;
		while (j < i)
		{
			if ((*cmp)(tab[j + 1], tab[j]) < 0)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
	}
}
