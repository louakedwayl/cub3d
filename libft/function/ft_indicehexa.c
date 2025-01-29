/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indicehexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:52:59 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:53:52 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_indicehexa(char *s)
{
	char	*retstring;
	int		i;
	int		j;

	i = 2;
	j = 0;
	retstring = malloc (sizeof(char) * 20);
	if (!retstring)
		return (NULL);
	ft_bzero(retstring, 20);
	retstring[0] = '0';
	retstring[1] = 'x';
	while (s[j])
	{
		retstring[i] = s[j];
		i++;
		j++;
	}
	free(s);
	return (retstring);
}
