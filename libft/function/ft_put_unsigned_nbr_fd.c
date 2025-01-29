/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_nbr_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:49:47 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:35:20 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../ft_printf.h"*/
#include <unistd.h>

static void	ft_md(unsigned int nb, unsigned int clone, int fd);
static void	ft_translate(unsigned int number, int fd);
static void	ft_udcm(unsigned int nb, unsigned int clone, int fd );
void		ft_put_unsigned_nbr_fd(unsigned int n, int fd);
static void	ft_m(unsigned int nb, unsigned int clone, int fd);

/*
int	main(void)
{
	ft_put_unsigned_nbr_fd(4294967295, 1);
	return (0);
}
*/

void	ft_put_unsigned_nbr_fd(unsigned int nb, int fd)
{
	unsigned int	clone;

	clone = nb;
	ft_md(nb, clone, fd);
	ft_m(nb, clone, fd);
	ft_udcm(nb, clone, fd);
	clone = nb % 10;
	ft_translate (clone, fd);
}

static void	ft_translate(unsigned int number, int fd)
{
	char	letter;

	letter = 48 + number;
	write (fd, &letter, 1);
}

static void	ft_udcm(unsigned int nb, unsigned int clone, int fd)
{
	if (clone > 999)
	{
		clone = clone / 1000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 99)
	{
		clone = clone / 100 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 9)
	{
		clone = clone / 10 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
}

static void	ft_m(unsigned int nb, unsigned int clone, int fd)
{
	if (clone > 999999)
	{
		clone = clone / 1000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 99999)
	{
		clone = clone / 100000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 9999)
	{
		clone = clone / 10000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
}

static void	ft_md(unsigned int nb, unsigned int clone, int fd)
{
	if (clone > 999999999)
	{
		clone = clone / 1000000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 99999999)
	{
		clone = clone / 100000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 9999999)
	{
		clone = clone / 10000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
}
