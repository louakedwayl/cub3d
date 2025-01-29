/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flaghexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:48:34 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:50:53 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_flaghexa(int *i, int *j, va_list args, char x)
{
	char	*s;
	int		count;

	s = ft_puthexa(va_arg(args, unsigned int), x);
	count = 0;
	while (s[count])
	{
		write(1, &s[count], 1);
		(*j)++;
		count++;
	}
	free (s);
	(*i)++;
}
