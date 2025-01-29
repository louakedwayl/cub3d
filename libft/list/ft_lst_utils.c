/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:04:48 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/23 09:19:33 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop(t_list **lst, int index)
{
	t_list	*current;
	void	*previous;
	int		i;

	if (!lst || *lst == NULL || (index < 0 && ft_lstsize(*lst) + index < 0))
		return (NULL);
	current = *lst;
	previous = NULL;
	if (index < 0)
		index = ft_lstsize(current) + index;
	if (index == 0)
		*lst = (*lst)->next;
	i = 0;
	while (i++ < index)
	{
		if (current->next == NULL)
			return (NULL);
		previous = (void *)current;
		current = current->next;
	}
	if (previous != NULL)
		((t_list *)previous)->next = current->next;
	previous = current->content;
	free(current);
	return (previous);
}

t_list	*ft_lstinsert(t_list **lst, int index, void *content)
{
	t_list	*new_lst;
	t_list	*current;
	int		i;

	if (!lst || (index < 0 && ft_lstsize(*lst) + index < 0))
		return (*lst);
	new_lst = ft_lstnew(content);
	if (new_lst == NULL)
		return (NULL);
	current = *lst;
	if (index < 0)
		index = ft_lstsize(current) + index + 1;
	if (index == 0)
	{
		new_lst->next = current;
		*lst = new_lst;
		return (new_lst);
	}
	i = 1;
	while (i++ < index && current->next != NULL)
		current = current->next;
	new_lst->next = current->next;
	current->next = new_lst;
	return (*lst);
}
