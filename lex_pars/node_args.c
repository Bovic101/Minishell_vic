/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:26:36 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/27 16:06:58 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_arg	*ft_arg_new(char *value)
{
	t_arg	*a;

	a = malloc(sizeof(t_arg));
	if (a == NULL)
		return (NULL);
	a->value = value;
	a->next = NULL;
	return (a);
}

t_arg	*ft_arg_last(t_arg *a)
{
	t_arg	*ptr;

	if (a == NULL)
		return (NULL);
	ptr = a;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_arg_add_back(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_arg_last(*lst);
	last->next = new;
}

void	add_args(char *value, t_arg **args)
{
	t_arg	*new;

	new = ft_arg_new(value);
	ft_arg_add_back(args, new);
}

void	ft_arg_print(t_arg **args)
{
	t_arg	*node;
	int		i;

	node = *args;
	i = 0;
	while (node)
	{
		printf("%i: %s\n", i, node->value);
		node = node->next;
		i++;
	}
	printf("\n");
}
