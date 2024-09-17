/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:09:00 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/16 12:28:20 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../minishell.h"

t_history	*ft_history_new(char *rvalue)
{
	t_history	*a;

	a = malloc(sizeof(t_history));
	if (a == NULL)
		return (NULL);
	a->rvalue = ft_strdup(rvalue);
	a->next = NULL;
	a->prev = NULL;
	return (a);
}

t_history	*ft_history_last(t_history *a)
{
	t_history	*ptr;

	if (a == NULL)
		return (NULL);
	ptr = a;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_history_add_back(t_history **lst, t_history *new)
{
	t_history	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_history_last(*lst);
	new->prev = last;
	last->next = new;
}

void	ft_free_history(t_history	**history)
{
	t_history	*node;
	t_history	*tmp;

	if (!history)
		return ;
	tmp = *history;
	while (tmp)
	{
		free(tmp->rvalue);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
	*history = NULL;
}

void	ft_history_print(t_history **history)
{
	t_history	*node;

	printf("History:\n");
	node = *history;
	while (node != NULL)
	{
		printf("%s\n", node->rvalue);
		node = node->next;
	}
	printf("\n");
}
*/