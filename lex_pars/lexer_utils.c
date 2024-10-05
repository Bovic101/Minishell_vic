/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:24:01 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 17:51:35 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_redir_in(char *s, int *i, int *len, enum e_tokentype *type)
{
	if (s[(*i) + 1] == '<')
	{
		(*len)++;
		(*i)++;
		*type = REDIR_IN2;
	}
	else
		*type = REDIR_IN;
	(*len)++;
	(*i)++;
}

void	lexer_redir_out(char *s, int *i, int *len, enum e_tokentype *type)
{
	if (s[(*i) + 1] == '>')
	{
		(*len)++;
		(*i)++;
		*type = REDIR_OUT2;
	}
	else
		*type = REDIR_OUT;
	(*len)++;
	(*i)++;
}

char	*lexer_double_quotes(char *s, int *i, int *len, enum e_tokentype *type)
{
	int		fl;
	char	*ptr;

	(*i)++;
	fl = 0;
	ptr = &s[*i];
	while (s[*i] != 34)
	{
		if (s[*i] == '$')
			fl = 1;
		(*len)++;
		(*i)++;
	}
	*type = WORD;
	if (fl == 1)
		*type = EXPAND_VAR_Q;
	(*i)++;
	return (ptr);
}

char	*lexer_single_quotes(char *s, int *i, int *len, enum e_tokentype *type)
{
	char	*ptr;

	(*i)++;
	ptr = &s[*i];
	while (s[*i] != 39)
	{
		(*len)++;
		(*i)++;
	}
	*type = WORD;
	(*i)++;
	return (ptr);
}

void	lexer_word(char *s, int *i, int *len, enum e_tokentype *type)
{
	int	fl;

	fl = 0;
	while (s[*i] != '\0' && s[*i] != ' ' && s[*i] != 34 && s[*i] != 39 \
			&& s[*i] != '|')
	{
		if (s[*i] == '$')
			fl = 1;
		(*len)++;
		(*i)++;
	}
	*type = WORD;
	if (fl == 1)
		*type = EXPAND_VAR;
}
