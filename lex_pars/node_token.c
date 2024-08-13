/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:43:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/04 15:55:48 by kdvarako         ###   ########.fr       */
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
/*
int	ft_lst_size(t_token *t)
{
	int		count;
	t_token	*ptr;

	if (t == NULL)
		return (0);
	ptr = t;
	count = 1;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

void	print_str(char *s, int len)  //remove later
{
	int i = 0;
	
	while (i < len)
	{
		printf("%c", s[i]);
		i++;
	}
	printf("\n");
}
*/

void	ft_lst_print(t_token **token)
{
	t_token	*node;

	node = *token;
	printf("| value | len | type |\n");
	while (node)
	{
		printf("%s ", node->ptr);
		printf("%d ", node->len);
		printf("%d\n", node->type);
		node = node->next;
	}
}
/*
void	ft_lst_print(t_token **token)
{
	t_token	*node;
	int		i;
	int		count;

	i = 0;
	count = ft_lst_size(*token);
	node = *token;
	while (i < count)
	{
		write(1, "node: ", 6);
		//ft_putstr_fd(node->ptr, 1);
		print_str(node->ptr, node->len);
		write(1, " len: ", 6);
		ft_putnbr_fd((node->len), 1);
		write(1, " type: ", 7);
		ft_putnbr_fd((node->type), 1);
		write(1, "\n", 1);
		node = node->next;
		i++;
	}
}*/
