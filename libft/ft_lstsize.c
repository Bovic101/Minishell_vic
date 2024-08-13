/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:17:44 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/26 12:25:09 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	if (lst == NULL)
		return (0);
	ptr = lst;
	count = 1;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}
