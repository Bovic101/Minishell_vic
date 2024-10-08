/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:37:36 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/08 03:15:22 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unclosed_quote_checker(const char *str)
{
	int			i;
	char		check;
	const char	*message;

	message = "Error:check for unclosed quote\n";
	i = 0;
	check = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && check == 0)
			check = str[i];
		else if (str[i] == check)
		{
			check = 0;
		}
		i++;
	}
	if (check != 0)
	{
		write(2, message, ft_strlen(message));
		return (1);
	}
	return (0);
}
