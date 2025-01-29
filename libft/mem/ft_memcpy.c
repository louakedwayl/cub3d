/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:31:34 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/17 10:16:51 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	uintptr_t	d;
	uintptr_t	s;

	if (n > 0 && dest)
	{
		d = (uintptr_t)dest;
		s = (uintptr_t)src;
		if ((d < s && d + n > s) || (s < d && s + n > d))
			return (ft_memmove(dest, src, n));
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
