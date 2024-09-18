/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:43:55 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/18 15:47:17 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_env(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
	{
		ft_env_print(env);
		set_value("_", ft_strdup("env"), env);
	}
}
