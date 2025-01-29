/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:17:35 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 19:55:57 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"

/*
   int main (void)
   {

   ft_printf("%p",LONG_MAX);
   }
   */

void	ft_flags(const char *format, int *i, int *j, va_list args)
{
	if (format[*i] == '%')
		ft_flagpercent(i, j);
	else if (format[*i] == 'c')
		ft_flagchar(i, j, args);
	else if (format[*i] == 's')
		ft_flagstring(i, j, args);
	else if (format[*i] == 'i' || format[*i] == 'd')
		ft_flagint(i, j, args);
	else if (format[*i] == 'u')
		ft_flagunsignedint(i, j, args);
	else if (format[*i] == 'x')
		ft_flaghexa(i, j, args, 'x');
	else if (format[*i] == 'X')
		ft_flaghexa(i, j, args, 'X');
	else if (format[*i] == 'p')
		ft_flagp(i, j, args);
}

int	ft_printf(const char *format, ...)
{
	int			i;
	int			j;
	va_list		args;

	i = 0;
	j = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_flags(format, &i, &j, args);
		}
		else
		{
			write(1, &format[i], 1);
			i++;
			j++;
		}
	}
	va_end(args);
	return (j);
}
