/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:37:36 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/21 00:33:53 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unclosed_quote_checker(const char *str)
{
	int	i;
	char	check;
	
	i = 0;
	check = 0; //no open quote when check is set to 0
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && check == 0)
		{
			check = str[i];
		}
		else if (str[i] == check) //quote opening
		{
			
			check = 0;//check current opening quote & close it
		}
		i++;
	}
	if (check != 0)//check if their is an unclosed quote after 1st loop
	{
		const char *message= "Error:check for unclosed quote\n";
		write(2, message, ft_strlen(message));
		return(1);
	}
	return(0);
}

