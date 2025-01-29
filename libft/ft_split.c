/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:57:37 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/29 19:59:11 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_split(char const *s, char c);
static int		ft_countword(char const *s, char c);
static int		len(char const *s, char c, int start);
static char		**ft_free2d(char **s, int *i);

/*
   int main (void)
   {
   char **test;
   char	string[] = "hello je suis un arbre.";
   test = ft_split(string, ' ');
   printf("%s\n", test[0]);
}
*/

char	**ft_split(char const *s, char c)
{
	char	**retval;
	int		i;
	int		start;

	if (!s)
		return (0);
	retval = malloc (sizeof(char *) * (ft_countword(s, c) + 1));
	if (!retval)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	while (i < ft_countword(s, c))
	{
		retval[i] = ft_substr(s, start, len(s, c, start));
		if (retval[i] == NULL)
			return (ft_free2d(retval, &i));
		start += len(s, c, start);
		while (s[start] == c)
			start++;
		i++;
	}
	retval[ft_countword(s, c)] = NULL;
	return (retval);
}

//calcul nombre de mot
static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

//calcul taille des string
static int	len(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start] && s[start] != c)
	{
		len++;
		start++;
	}
	return (len);
}

static char	**ft_free2d(char **s, int *i)
{
	while (*i > 0)
	{
		*i = *i - 1;
		free (s[*i]);
	}
	free(s);
	return (NULL);
}
