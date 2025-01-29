/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:31:34 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/25 12:16:35 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char	v;
	size_t	i;

	if (!s)
		return (s);
	v = (char)c;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = v;
		i++;
	}
	return (s);
}
