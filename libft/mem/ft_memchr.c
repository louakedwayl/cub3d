/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:33:24 by llebioda          #+#    #+#             */
/*   Updated: 2024/11/06 16:37:12 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	v;

	if (!s)
		return (0);
	v = (char)c;
	while (n > 0)
	{
		if (*(char *)s == v)
			return ((void *)s);
		s++;
		n--;
	}
	return (0);
}
