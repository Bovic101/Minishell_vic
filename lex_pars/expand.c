/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:22:43 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 03:21:15 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_len_key(char *ptr, int *i, int *len_key)
{
	while (ptr[*i] != '\0' && ((ptr[*i] >= 'a' && ptr[*i] <= 'z')
			|| (ptr[*i] >= 'A' && ptr[*i] <= 'Z') || ptr[*i] == '_'))
	{
		(*len_key)++;
		(*i)++;
	}
}

char	*find_key(char *ptr, char **s1, char **s2)
{
	char	*key;
	int		i;
	int		len_key;

	i = 0;
	key = NULL;
	len_key = 0;
	while (ptr[i] != '\0' && ptr[i] != '$')
		i++;
	*s1 = ft_strndup(ptr, i);
	i++;
	key = &ptr[i];
	if (ptr[i] == 63)
	{
		len_key = 1;
		i++;
	}
	else
	{
		ft_len_key(ptr, &i, &len_key);
	}
	*s2 = ft_strndup(&ptr[i], (ft_strlen(ptr) - i));
	return (ft_strndup(key, len_key));
}

/*
if key == "?"
$? - status of the most recently executed pipeline
-> value of the variable "exit_status" in env
*/
char	*join_parts(char *str, t_env **env)
{
	char	*key;
	char	*value;
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	key = find_key(str, &s1, &s2);
	free(str);
	if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(*env[0]->exit_status);
	else
		value = ft_strdup(get_value(key, env));
	if (value == NULL)
		return (free(key), ft_strjoin_free(s1, s2));
	return (free(key), ft_strjoin_free(ft_strjoin_free(s1, value), s2));
}

char	*expand(char *ptr, int len, t_env **env)
{
	char	*str;

	str = NULL;
	str = ft_strndup(ptr, len);
	if (str == NULL)
		return (NULL);
	while (ft_strchr(str, '$') != NULL)
	{
		str = join_parts(str, env);
	}
	return (str);
}
