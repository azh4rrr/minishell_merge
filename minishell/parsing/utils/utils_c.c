/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:00:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 15:05:36 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	skip_whitespace(char *str, int start)
{
	while (str[start] && is_whitespace(str[start]))
		start++;
	return (start);
}

int	find_next_char_outside_quotes(char *str, char target, int start)
{
	int	i;
	int	in_single;
	int	in_double;

	i = start;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == target && !in_single && !in_double)
			return (i);
		i++;
	}
	return (-1);
}

int	count_token_segment(char *str, int start, int delimiter)
{
	int	i;
	int	in_single;
	int	in_double;

	i = start;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == delimiter && !in_single && !in_double)
			return (i);
		i++;
	}
	return (i);
}

int	count_tokens_with_quotes(char *str, char delimiter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == delimiter)
			i++;
		if (!str[i])
			break ;
		count++;
		i = count_token_segment(str, i, delimiter);
	}
	return (count);
}
