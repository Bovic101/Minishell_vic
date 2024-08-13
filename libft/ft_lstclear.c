/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:20:26 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/26 16:10:23 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*before;

	if (lst)
	{
		ptr = *lst;
		before = *lst;
		while (ptr != NULL)
		{
			del(ptr->content);
			ptr = ptr->next;
			free(before);
			before = ptr;
		}
		*lst = NULL;
	}
}
