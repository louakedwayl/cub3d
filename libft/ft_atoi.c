/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:11 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/02 10:40:39 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	a;
	int	is_negative;

	if (nptr == NULL)
		return (0);
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	is_negative = 0;
	if (*nptr == '-')
		is_negative = 1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	a = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		a = a * 10 + (*nptr - '0');
		nptr++;
	}
	if (is_negative == 1)
		return (-a);
	return (a);
}

static int	check_int_overflow(const char *nptr, int is_negative)
{
	int	len;

	while (*nptr == '0')
	{
		nptr++;
		if (*nptr < '0' || *nptr > '9')
			return (1);
	}
	len = 0;
	while (nptr[len] >= '0' && nptr[len] <= '9')
		len++;
	if (len > 10 || len <= 0)
		return (0);
	if (len < 10)
		return (1);
	if (is_negative == 1)
		return (ft_strncmp(nptr, "2147483648", 10) <= 0);
	return (ft_strncmp(nptr, "2147483647", 10) <= 0);
}

int	ft_atoi_valid(const char *nptr)
{
	int	is_negative;

	if (nptr == NULL)
		return (0);
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	is_negative = 0;
	if (*nptr == '-')
		is_negative = 1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	return (check_int_overflow(nptr, is_negative));
}

int	ft_atoi_safe(const char *nptr, int error_ret_val)
{
	if (ft_atoi_valid(nptr) == 0)
		return (error_ret_val);
	return (ft_atoi(nptr));
}
