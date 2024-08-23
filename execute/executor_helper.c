/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/23 14:11:51 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
execve() function requires array to execute a commannd
**/
//convert linked_lst arg(t_arg) to an array of strings
char	**arg_to_array_converter(t_arg *arg , char *command)
{
	int	i;
	char	**argv;
	int	arg_counter = 1;//starting from 1 as a first command
	t_arg	*cur_arg = arg;
	
	while (cur_arg)
	{
		arg_counter++;
		cur_arg = cur_arg->next;
	}
	argv =(char **)malloc(sizeof(char *) * (arg_counter + 1));
	if (!argv)
	{
		return(NULL);
	}
	argv[0] = command;
	cur_arg = arg;
	i = 1;
	while (cur_arg)
	{
		argv[i++] = cur_arg->value;
		cur_arg = cur_arg->next;
	}
	argv[i] = NULL;//end of array
	return(argv);
}