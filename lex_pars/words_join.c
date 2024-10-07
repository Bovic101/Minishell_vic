/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/07 14:41:59 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_wordjoin(char *value, char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!value || !str)
		return (NULL);
	new = malloc(ft_strlen(value) + ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (value[i] != '\0')
	{
		new[i] = value[i];
		i++;
	}
	j = 0;
	while (str[j] != '\0')
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(value);
	return (new);
}

char	*save_word(t_token **pnode, t_env **env)
{
	char	*str;
	char	*value;
	t_token	*node;

	node = *pnode;
	str = NULL;
	value = NULL;
	value = malloc(1);
	if (!value)
		return (NULL);
	value[0] = '\0';
	while (node != NULL && node->type != SEPARATOR && node->type != PIPE)
	{
		if (node->type == WORD)
			str = ft_strndup(node->ptr, node->len);
		else if (node->type == EXPAND_VAR || node->type == EXPAND_VAR_Q)
			str = expand(node->ptr, node->len, env);
		value = ft_wordjoin(value, str);
		free (str);
		*pnode = node;
		node = node->next;
	}
	return (value);
}
