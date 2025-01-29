/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayl <wayl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:18:54 by wlouaked          #+#    #+#             */
/*   Updated: 2024/07/27 21:46:16 by wayl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(char *s, int c);
size_t	gnl_strlen(char *s);
char	*substr2(char *s, unsigned int start, size_t len);
void	ft_free(char **str);
char	*get_next_line(int fd);
void	gnl_bzero(void *s, size_t n);

#endif
