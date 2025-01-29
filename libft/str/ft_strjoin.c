/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:08:51 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/06 15:14:42 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = malloc(len_s1 + len_s2 + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			dst[i] = s1[i];
		if (i < len_s2)
			dst[i + len_s1] = s2[i];
		i++;
	}
	dst[len_s1 + len_s2] = '\0';
	return (dst);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	dst = malloc(len_s1 + len_s2 + len_s3 + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1 || i < len_s2 || i < len_s3)
	{
		if (i < len_s1)
			dst[i] = s1[i];
		if (i < len_s2)
			dst[i + len_s1] = s2[i];
		if (i < len_s3)
			dst[i + len_s1 + len_s2] = s3[i];
		i++;
	}
	dst[len_s1 + len_s2 + len_s3] = '\0';
	return (dst);
}

char	*ft_strjoin_all(const char **tab, const char *sep)
{
	char	*dst;
	size_t	total_len;
	int		i;
	size_t	j;

	if (tab == NULL || *tab == NULL)
		return (ft_strdup(""));
	total_len = 0;
	i = 0;
	while (tab[i] != NULL)
		total_len += ft_strlen(tab[i++]);
	if (sep != NULL)
		total_len += ft_strlen(sep) * (i - 1);
	dst = ft_calloc(total_len + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		j += ft_strlcpy(&(dst[j]), tab[i++], total_len - j + 1);
		if (j <= total_len && sep != NULL)
			j += ft_strlcpy(&(dst[j]), sep, total_len - j + 1);
	}
	return (dst);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

char	*ft_strjoin3_free(char *s1, char *s2, char *s3)
{
	char	*temp;

	temp = ft_strjoin3(s1, s2, s3);
	free(s1);
	free(s2);
	free(s3);
	return (temp);
}
