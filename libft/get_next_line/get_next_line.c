/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayl <wayl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:44:17 by wlouaked          #+#    #+#             */
/*   Updated: 2024/07/27 21:46:02 by wayl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fre(char **ptstring)
{
	free(*ptstring);
	*ptstring = NULL;
}

// retourne la postion du premier \n ou de la fin de la chaine si il ny en a pas
size_t	next(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
	{
		i++;
	}
	return (i);
}

char	*ft_read(int fd, char *retstring, char **ptstash)
{
	char	*buff;
	char	*tempfree;
	int		retread;

	buff = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (fre(&retstring), NULL);
	gnl_bzero(buff, BUFFER_SIZE + 1);
	while (!gnl_strchr(buff, '\n'))
	{
		gnl_bzero(buff, BUFFER_SIZE + 1);
		retread = read (fd, buff, BUFFER_SIZE);
		retstring = gnl_strjoin(retstring, buff);
		if (retread < 0)
			return (fre(&buff), fre(ptstash), fre(&retstring), NULL);
		if (retread != BUFFER_SIZE && retread >= 1)
			break ;
		if (retread == 0)
			return (fre(&buff), fre(ptstash), retstring);
	}
	fre(ptstash);
	*ptstash = substr2(retstring, next(retstring) + 1, gnl_strlen(retstring));
	tempfree = retstring;
	retstring = substr2(retstring, 0, next(retstring) + 1);
	return (fre(&tempfree), fre(&buff), retstring);
}

char	*get_next_line(int fd)
{
	static char		*stash = NULL;
	char			*retstring;
	char			*tempfree;

	retstring = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	if (stash)
	{
		if (gnl_strchr(stash, '\n'))
		{
			retstring = substr2(stash, 0, next(stash) + 1);
			if (!retstring)
				return (fre(&stash), NULL);
			tempfree = stash;
			stash = substr2(stash, next(stash) + 1, gnl_strlen(stash));
			return (fre(&tempfree), retstring);
		}
		retstring = gnl_strjoin(retstring, stash);
	}
	retstring = ft_read(fd, retstring, &stash);
	if (!retstring || !retstring[0])
		return (fre(&stash), fre(&retstring), NULL);
	return (retstring);
}

/*
int	main(void )
{
	int	fd;
	char	*line;


	fd = open("texte.txt", O_RDONLY);

	while((line = get_next_line(fd)) != NULL)
	{
		printf("line '%s'\n", line);
		free(line);
	}

	return (0);
}
*/
