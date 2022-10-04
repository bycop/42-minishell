/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:47:04 by bycop          #+#    #+#             */
/*   Updated: 2021/03/19 10:13:21 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*list;

	list = ft_lstnew(f(lst->content));
	if (!lst || !list)
		return (NULL);
	res = list;
	while (lst->next)
	{
		lst = lst->next;
		list->next = ft_lstnew(f(lst->content));
		if (!list->next)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		list = list->next;
	}
	return (res);
}
