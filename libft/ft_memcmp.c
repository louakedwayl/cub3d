/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:40:53 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/28 16:29:59 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	*string2;

	string = malloc(sizeof(char) * n);
	string2 = malloc(sizeof(char) * n);
	string = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (string[i] > string2[i])
		{
			return (1);
		}
		if (string[i] < string2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
