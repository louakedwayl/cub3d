/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfirst_occurence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:41:08 by llebioda          #+#    #+#             */
/*   Updated: 2025/01/02 13:32:32 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfirst_occ(t_list *lst, int (*f)(void *, void *), void *params)
{
	t_list	*current;

	if (lst == NULL || f == NULL)
		return (NULL);
	current = lst;
	while (current != NULL)
	{
		if ((*f)(params, current->content) == 1)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	ft_lstfirst_occ_index(t_list *lst, int (*f)(void *, void *), void *params)
{
	t_list	*current;
	int		i;

	if (lst == NULL || f == NULL)
		return (-1);
	current = lst;
	i = 0;
	while (current != NULL)
	{
		if ((*f)(params, current->content) == 1)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}
