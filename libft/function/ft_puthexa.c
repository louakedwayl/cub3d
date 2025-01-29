/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:43:46 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:46:46 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_puthexa(unsigned int nbr, char x);
char	*ft_returnstring(char *string);

/*
int main (void)
{
	ft_printf ("%x", 45431);
}
*/

char	*ft_puthexa(unsigned int nbr, char x)
{
	char	*s;
	char	retval[10];
	char	*retval2;
	int		i;

	i = 0;
	ft_bzero(retval, 10);
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

char	*ft_returnstring(char *string)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*retstring;

	i = 0;
	j = ft_strlen(string);
	k = j;
	retstring = malloc(sizeof(char) * 20);
	if (!retstring)
		return (NULL);
	ft_bzero(retstring, 20);
	while (i < k)
	{
		j--;
		retstring[i] = string[j];
		i++;
	}
	retstring[i] = '\0';
	return (retstring);
}
