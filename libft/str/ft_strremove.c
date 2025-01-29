/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:07:53 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/23 18:33:33 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_count(const char *str, const char *set)
{
	int	i;

	if (str == NULL || set == NULL)
		return (-1);
	i = 0;
	while (*str)
	{
		if (ft_strcontains(set, *str) == 0)
			i++;
		str++;
	}
	return (i);
}

char	*ft_strremove(const char *str, const char *set)
{
	char	*s;
	int		len;
	int		i;

	if (str == NULL)
		return (NULL);
	len = get_count(str, set);
	if (len == -1 || len == (int)ft_strlen(str))
		return (ft_strdup(str));
	s = ft_calloc(len + 1, sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (ft_strcontains(set, *str) == 0)
			s[i++] = *str;
		str++;
	}
	return (s);
}
