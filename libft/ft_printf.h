/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:57:40 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/14 17:19:22 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
void	ft_flagpercent(int *i, int *j);
void	ft_flagchar(int *i, int *j, va_list args);
void	ft_flagstring(int *i, int *j, va_list args);
void	ft_flags(const char *format, int *i, int *j, va_list args);
void	ft_putnbr_fd(int n, int fd);
void	ft_put_unsigned_nbr_fd(unsigned int n, int fd);
void	ft_flagint(int *i, int *j, va_list args);
void	ft_flagunsignedint(int *i, int *j, va_list args);
char	*ft_puthexa(unsigned int nbr, char x);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	ft_flaghexa(int *i, int *j, va_list args, char x);
char	*ft_returnstring(char *string);
char	*ft_puthexa2(unsigned long nbr, char x);
char	*ft_indicehexa(char *s);
void	ft_flagp(int *i, int *j, va_list args);

#endif
