/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:09:02 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/03 12:08:42 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_str(char **tab, const char *str, const char *sep, int tablen);
static int	copy(char **tab, const char *str, int *offset, int *len);
static int	count(const char *str, const char *sep);

char	**ft_split(const char *s, const char *set)
{
	char	**tab;
	int		tab_len;
	int		i;

	tab_len = count(s, set) + 1;
	tab = ft_calloc(tab_len + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (split_str(tab, s, set, tab_len) == 0)
	{
		i = 0;
		while (i < tab_len)
		{
			if (tab[i] == NULL)
			{
				while (i >= 0)
					free(tab[i--]);
				free(tab);
				return (NULL);
			}
			i++;
		}
	}
	return (tab);
}

static int	split_str(char **tab, const char *str, const char *sep, int tablen)
{
	char	*s;
	int		i;
	int		offset;
	int		len;

	s = (char *)str;
	i = 0;
	offset = 0;
	len = 0;
	while (*s && i < tablen)
	{
		if (ft_strcontains(sep, *s++) == 1)
		{
			if (len > 0 && !copy(&(tab[i++]), str, &offset, &len))
				return (0);
			offset++;
		}
		else
			len++;
	}
	tab[i] = ft_strndup(str + offset, len);
	if (tab[i] == NULL)
		return (0);
	return (1);
}

static int	copy(char **tab, const char *str, int *offset, int *len)
{
	char	*r;

	r = ft_strndup(str + *offset, *len);
	if (r == NULL)
		return (0);
	*tab = r;
	*offset += *len;
	*len = 0;
	return (1);
}

static int	count(const char *str, const char *sep)
{
	int	count;
	int	was_split;

	if (sep == NULL || *sep == '\0')
		return (0);
	count = 0;
	was_split = 1;
	while (*str)
	{
		if (ft_strcontains(sep, *str) == 1)
		{
			if (was_split == 0)
				count++;
			was_split = 1;
		}
		else
			was_split = 0;
		str++;
	}
	return (count);
}
