/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayl <wayl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:44:28 by wlouaked          #+#    #+#             */
/*   Updated: 2024/07/27 21:58:29 by wayl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc (sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	s3 = malloc (sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!s3)
		return (free(s1), s1 = NULL, NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (free(s1), s1 = NULL, s3);
}

void	gnl_bzero(void *s, size_t n)
{
	char	*string;
	size_t	i;

	string = s;
	i = 0;
	while (i < n)
	{
		string[i] = '\0';
		i++;
	}
}

char	*gnl_strchr(char *s, int c)
{
	size_t			i;
	size_t			len;

	i = 0;
	len = gnl_strlen(s);
	while (i <= len)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		if (!s[i] && !c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*substr2(char *s, unsigned int start, size_t end)
{
	char			*string;
	unsigned int	i;

	if (start >= gnl_strlen(s))
	{
		string = malloc (sizeof(char));
		if (!string)
			return (NULL);
		string[0] = '\0';
		return (string);
	}
	string = malloc (sizeof(char) *(end - start + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (start < end)
	{
		string[i] = s[start];
		i++;
		start++;
	}
	string[i] = '\0';
	return (string);
}

/*
   int main (void)
   {
   char *string = "hello\n world";

   printf ("%ld", next_line(string));
   }
   */
