/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:43 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:32:15 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_flagstring(int *i, int *j, va_list args)
{
	char	*string;
	int		k;

	(*i)++;
	string = (char *)va_arg(args, char *);
	if (!string)
	{
		write (1, "(null)", 6);
		(*j) += 6;
		return ;
	}
	k = 0;
	while (string[k])
	{
		write (1, &string[k], 1);
		k++;
	}
	while (k > 0)
	{
		(*j)++;
		k--;
	}
}
