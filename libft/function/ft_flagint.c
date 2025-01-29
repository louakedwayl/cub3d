/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:25:56 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:28:50 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_sizeflagint(int temp, int **j);

void	ft_flagint(int *i, int *j, va_list args)
{
	int	temp;

	(*i)++;
	temp = 0;
	temp = va_arg(args, int);
	ft_putnbr_fd(temp, 1);
	ft_sizeflagint(temp, &j);
}

static void	ft_sizeflagint(int temp, int **j)
{
	if ((**j)++ == -100 || temp < 0)
	{
		(**j)++;
		temp = -temp;
		if (temp == -2147483648)
			temp = temp - 1;
	}
	if (temp > 9)
		(**j)++;
	if (temp > 99)
		(**j)++;
	if (temp > 999)
		(**j)++;
	if (temp > 9999)
		(**j)++;
	if (temp > 99999)
		(**j)++;
	if (temp > 999999)
		(**j)++;
	if (temp > 9999999)
		(**j)++;
	if (temp > 99999999)
		(**j)++;
	if (temp > 999999999)
		(**j)++;
}
