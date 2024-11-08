/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:40:29 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 14:32:17 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
function checks if there is a flag "-n" or "-nnn..." &
returns 0 if not or 1 if yes
*/
int	ft_if_newline(char *s)
{
	unsigned int	i;

	i = 1;
	if (s != NULL && s[0] == '-')
	{
		while (s[i] != '\0')
		{
			if (s[i] != 'n')
				break ;
			i++;
		}
		if (i == ft_strlen(s))
			return (1);
	}
	return (0);
}

void	echo_print(t_arg *arg, int len)
{
	while (arg != NULL)
	{
		printf("%s", arg->value);
		if (len > 0)
			printf(" ");
		arg = arg->next;
		len--;
	}
}

int	exe_echo(t_parc *node)
{
	t_arg	*arg;
	int		fl_n;
	int		len;

	if (node->args != NULL)
	{
		arg = node->args;
		len = ft_size_arg(arg) - 1;
		fl_n = ft_if_newline(arg->value);
		if (fl_n == 1)
		{
			arg = arg->next;
			len--;
		}
		echo_print(arg, len);
		if (fl_n == 0)
			printf("\n");
	}
	else
		printf("\n");
	return (0);
}
