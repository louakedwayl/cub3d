/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:37:00 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:41:04 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_flagp(int *i, int *j, va_list args)
{
	char				*s;
	char				*retstring;
	int					count;
	unsigned long int	temp;

	temp = va_arg(args, unsigned long);
	if (!temp)
	{
		write(1, "(nil)", 5);
		(*i)++;
		(*j) += 5;
		return ;
	}
	s = ft_puthexa2(temp, 'x');
	retstring = ft_indicehexa(s);
	count = 0;
	while (retstring[count])
	{
		write(1, &retstring[count], 1);
		(*j)++;
		count++;
	}
	(*i)++;
	free(retstring);
}
