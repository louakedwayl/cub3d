/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:34:59 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/03 12:05:18 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	len;
	size_t	i;

	if (src == NULL)
		return (NULL);
	len = ft_strlen(src);
	dst = malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *src, unsigned int n)
{
	char			*dst;
	unsigned int	src_len;
	unsigned int	i;

	if (src == NULL || n == 0)
		return (NULL);
	src_len = 0;
	while (src[src_len] && src_len < n)
		src_len++;
	dst = malloc(src_len + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
