/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:09:07 by azhar             #+#    #+#             */
/*   Updated: 2025/07/20 15:25:24 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quotes_and_skip(t_split *split)
{
	while (split->str[split->i])
	{
		if (split->str[split->i] == '\'' && !split->in_double)
			split->in_single = !split->in_single;
		else if (split->str[split->i] == '"' && !split->in_single)
			split->in_double = !split->in_double;
		if (split->str[split->i] == split->delimiter && !split->in_single
			&& !split->in_double)
			break ;
		split->i++;
	}
}

int	count_and_skip_delimiters(t_split *split)
{
	while (split->str[split->i])
	{
		while (split->str[split->i] == split->delimiter && !split->in_single
			&& !split->in_double)
			split->i++;
		if (!split->str[split->i])
			break ;
		split->token_count++;
		update_quotes_and_skip(split);
	}
	return (split->token_count);
}

char	*extract_single_token(char *str, int start, int end)
{
	char	*token;
	int		i;

	token = malloc(end - start + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (start < end)
	{
		token[i] = str[start];
		i++;
		start++;
	}
	token[i] = '\0';
	return (token);
}

char	**allocate_and_extract(t_split *split)
{
	split->tokens = malloc(sizeof(char *) * (split->token_count + 1));
	if (!split->tokens)
		return (NULL);
	split->i = 0;
	split->token_idx = 0;
	split->in_single = 0;
	split->in_double = 0;
	while (split->str[split->i] && split->token_idx < split->token_count)
	{
		while (split->str[split->i] == split->delimiter && !split->in_single
			&& !split->in_double)
			split->i++;
		if (!split->str[split->i])
			break ;
		split->start = split->i;
		update_quotes_and_skip(split);
		split->tokens[split->token_idx] = extract_single_token(split->str,
				split->start, split->i);
		if (!split->tokens[split->token_idx])
			return (cleanup_tokens(split->tokens, split->token_idx), NULL);
		split->token_idx++;
	}
	split->tokens[split->token_idx] = NULL;
	return (split->tokens);
}

char	**quote_aware_split(char *str, char delimiter)
{
	t_split	split;
	char	**empty_result;

	if (!str)
		return (NULL);
	init_split(&split, str, delimiter);
	count_and_skip_delimiters(&split);
	if (split.token_count == 0)
	{
		empty_result = malloc(sizeof(char *));
		if (empty_result)
			empty_result[0] = NULL;
		return (empty_result);
	}
	split.i = 0;
	split.in_single = 0;
	split.in_double = 0;
	return (allocate_and_extract(&split));
}
