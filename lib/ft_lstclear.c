/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:36:22 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/21 11:29:44 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*next;

	list = *lst;
	if (!list)
	while (list)
	{
		next = list->next;
		del(list->content->key);
		del(list->content->value);
		del(list->content);
		free(list);
		list = next;
	}	return ;
	
	*lst = 0;
}
