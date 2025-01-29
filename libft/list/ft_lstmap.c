/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:42:07 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/24 06:13:27 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*temp;
	void	*content;

	if (f == NULL)
		return (NULL);
	r = NULL;
	while (lst != NULL)
	{
		content = (*f)(lst->content);
		temp = ft_lstnew(content);
		if (temp == NULL)
		{
			if (del != NULL)
				del(content);
			ft_lstclear(&r, del);
			return (NULL);
		}
		ft_lstadd_back(&r, temp);
		lst = lst->next;
	}
	return (r);
}
