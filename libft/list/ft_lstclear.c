/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:41:51 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/24 06:12:43 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ls;
	t_list	*temp;

	if (lst == NULL)
		return ;
	ls = *lst;
	while (ls != NULL)
	{
		if (del != NULL)
			(*del)(ls->content);
		temp = ls->next;
		free(ls);
		ls = temp;
	}
	*lst = NULL;
}
