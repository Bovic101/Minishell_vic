/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:47:33 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/27 11:22:59 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnewdel(void *content, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;

	if (lst == NULL)
		return (NULL);
	newlst = ft_lstnewdel(f(lst->content), del);
	if (newlst == NULL)
	{
		ft_lstclear(&newlst, del);
		return (NULL);
	}
	newlst->next = ft_lstmap(lst->next, f, del);
	return (newlst);
}

static t_list	*ft_lstnewdel(void *content, void (*del)(void *))
{
	t_list	*a;

	a = ft_lstnew(content);
	if (!a)
	{
		del(content);
		return (NULL);
	}
	return (a);
}
