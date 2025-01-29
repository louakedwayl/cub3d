/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagunsignedint.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:51:34 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:43:03 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_sizeflag_unsignedint(unsigned int temp, int **j);

void	ft_flagunsignedint(int *i, int *j, va_list args)
{
	unsigned int	temp;

	(*i)++;
	temp = 0;
	temp = va_arg(args, unsigned int);
	ft_put_unsigned_nbr_fd(temp, 1);
	ft_sizeflag_unsignedint(temp, &j);
}

static void	ft_sizeflag_unsignedint(unsigned int temp, int **j)
{
	(**j)++;
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
