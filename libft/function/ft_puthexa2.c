/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:32:47 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:34:07 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_puthexa2(unsigned long nbr, char x)
{
	char	*s;
	char	retval[20];
	char	*retval2;
	int		i;

	i = 0;
	ft_bzero(retval, 20);
	s = "0123456789abcdef";
	if (x == 'X')
		s = "0123456789ABCDEF";
	while (nbr > 16)
	{
		retval[i++] = s[nbr % 16];
		nbr = nbr / 16;
	}
	retval[i] = s[nbr % 16];
	retval[i + 1] = '\0';
	retval2 = ft_returnstring(retval);
	if (retval2 && nbr == 16)
	{
		retval2[0] = '1';
		retval2[1] = '0';
		retval2[2] = '\0';
	}
	return (retval2);
}
