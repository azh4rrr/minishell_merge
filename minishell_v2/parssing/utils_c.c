/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:00:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/14 17:01:49 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/* Skip whitespace characters in a string */
int	skip_whitespace(char *str, int start)
{
	while (str[start] && is_whitespace(str[start]))
		start++;
	return (start);
}

/* Find the next occurrence of a character outside quotes */
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

/* Count tokens in a string, respecting quotes */
int	count_tokens_with_quotes(char *str, char delimiter)
{
	int count = 0;
	int i = 0;
	int in_single = 0;
	int in_double = 0;

	if (!str)
		return (0);

	while (str[i])
	{
		// Skip leading delimiters
		while (str[i] == delimiter && !in_single && !in_double)
			i++;

		if (!str[i])
			break ;

		count++;

		// Skip until next delimiter (outside quotes) or end of string
		while (str[i])
		{
			if (str[i] == '\'' && !in_double)
				in_single = !in_single;
			else if (str[i] == '"' && !in_single)
				in_double = !in_double;
			else if (str[i] == delimiter && !in_single && !in_double)
				break ;
			i++;
		}
	}

	return (count);
}