/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:43:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/17 13:22:54 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lst_new(int len, char *ptr, enum e_tokentype type)
{
	t_token	*a;

	a = malloc(sizeof(t_token));
	if (a == NULL)
		return (NULL);
	a->len = len;
	a->ptr = ptr;
	a->type = type;
	a->next = NULL;
	return (a);
}

t_token	*ft_lst_last(t_token *t)
{
	t_token	*ptr;

	if (t == NULL)
		return (NULL);
	ptr = t;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_lst_add_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (new == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_lst_last(*token);
	last->next = new;
}

void	ft_print_type(enum e_tokentype type)
{
	if (type == 0)
		printf("WORD \n");
	else if (type == 1)
		printf("SEPARATOR \n");
	else if (type == 2)
		printf("REDIR_IN \n");
	else if (type == 3)
		printf("REDIR_OUT \n");
	else if (type == 4)
		printf("REDIR_IN2 \n");
	else if (type == 5)
		printf("REDIR_OUT2 \n");
	else if (type == 6)
		printf("EXPAND_VAR \n");
	else if (type == 7)
		printf("EXPAND_VAR_Q \n");
	else if (type == 8)
		printf("PIPE \n");
}

void	ft_lst_print(t_token **token)
{
	t_token	*node;
	int		i;

	node = *token;
	printf("----------------------\n");
	printf("| value | len | type |\n");
	printf("----------------------\n");
	while (node)
	{
		i = 0;
		while (i < node->len)
		{
			write(1, &node->ptr[i], 1);
			i++;
		}
		printf("| %d | ", node->len);
		ft_print_type(node->type);
		node = node->next;
	}
}
