/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:36:52 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 18:19:56 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_fully_quoted(char *str)
{
	int		len;
	char	quote_type;
	int		i;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"' && str[len
				- 1] == '"'))
	{
		quote_type = str[0];
		i = 1;
		while (i < len - 1)
		{
			if (str[i] == quote_type)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	find_token_boundaries(char *cmd_str, t_paredir *red)
{
	red->i = 0;
	while (cmd_str[red->i] && (cmd_str[red->i] == ' '
			|| cmd_str[red->i] == '\t'))
		red->i++;
	red->start = red->i;
	if (cmd_str[red->i] == '"' || cmd_str[red->i] == '\'')
	{
		red->quote = cmd_str[red->i];
		red->i++;
		while (cmd_str[red->i] && cmd_str[red->i] != red->quote)
			red->i++;
		if (cmd_str[red->i] == red->quote)
			red->i++;
	}
	else
	{
		while (cmd_str[red->i] && cmd_str[red->i] != ' '
			&& cmd_str[red->i] != '\t')
			red->i++;
	}
	red->end = red->i;
}

static char	*extract_first_token(char *cmd_str)
{
	t_paredir	red;
	char		*first_token;

	find_token_boundaries(cmd_str, &red);
	if (red.start == red.end)
		return (NULL);
	first_token = malloc(red.end - red.start + 1);
	if (!first_token)
		return (NULL);
	ft_strncpy(first_token, cmd_str + red.start, red.end - red.start);
	first_token[red.end - red.start] = '\0';
	return (first_token);
}

int	first_token_is_fully_quoted(char *cmd_str)
{
	char	*first_token;
	int		result;

	if (!cmd_str)
		return (0);
	first_token = extract_first_token(cmd_str);
	if (!first_token)
		return (0);
	result = is_fully_quoted(first_token);
	free(first_token);
	return (result);
}

/* Check if command contains only quoted segments and spaces */
int	contains_only_quotes_and_spaces(char *cmd_str)
{
	int	i;
	int	in_quotes;
	int	has_quotes;

	if (!cmd_str)
		return (0);
	i = 0;
	in_quotes = 0;
	has_quotes = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
		{
			in_quotes = !in_quotes;
			has_quotes = 1;
		}
		else if (!in_quotes && cmd_str[i] != ' ' && cmd_str[i] != '\t')
			return (0);
		i++;
	}
	return (has_quotes);
}
