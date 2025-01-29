/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:19:03 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/02 13:54:53 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*find;

	if (!s)
		return (0);
	find = 0;
	while (*s)
	{
		if (*s == (char)c)
			find = s;
		s++;
	}
	if (*s == (char)c)
		find = s;
	return ((char *)find);
}
