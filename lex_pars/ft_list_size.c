/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:33:14 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/02 12:45:51 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//find size of t_parc structure - count nodes
int	ft_size_parc(t_parc *lst)
{
	int		count;
	t_parc	*ptr;

	count = 1;
	ptr = lst;
	if (lst == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

//find size of t_arg structure - count nodes
int	ft_size_arg(t_arg *lst)
{
	int		count;
	t_arg	*ptr;

	count = 1;
	ptr = lst;
	if (lst == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

//find size of t_redirect structure - count nodes
int	ft_size_redirect(t_redirect *lst)
{
	int			count;
	t_redirect	*ptr;

	count = 1;
	ptr = lst;
	if (lst == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

//find size of t_env structure - count nodes except _exit_code & value=NULL
int	ft_size_env(t_env *lst)
{
	int		count;
	t_env	*ptr;

	count = 1;
	ptr = lst;
	if (lst == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		if (ptr->value != 0 && ft_strcmp(ptr->key, "_exit_code") != 0)
			count++;
		ptr = ptr->next;
	}
	return (count);
}
