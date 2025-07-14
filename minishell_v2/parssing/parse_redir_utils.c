/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:36:52 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/14 15:37:04 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../minishell.h"

int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

int	is_inside_quotes(char *str, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i <= pos && str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

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

int	first_token_is_fully_quoted(char *cmd_str)
{
	t_paredir	red;

	if (!cmd_str)
		return (0);
	red.i = 0;
	while (cmd_str[red.i] && (cmd_str[red.i] == ' ' || cmd_str[red.i] == '\t'))
		red.i++;
	if (!cmd_str[red.i])
		return (0);
	red.start = red.i;
	if (cmd_str[red.i] == '"' || cmd_str[red.i] == '\'')
	{
		red.quote = cmd_str[red.i];
		red.i++;
		while (cmd_str[red.i] && cmd_str[red.i] != red.quote)
			red.i++;
		if (cmd_str[red.i] == red.quote)
			red.i++;
	}
	else
	{
		while (cmd_str[red.i] && cmd_str[red.i] != ' '
			&& cmd_str[red.i] != '\t')
			red.i++;
	}
	red.end = red.i;
	red.first_token = malloc(red.end - red.start + 1);
	if (!red.first_token)
		return (0);
	ft_strncpy(red.first_token, cmd_str + red.start, red.end - red.start);
	red.first_token[red.end - red.start] = '\0';
	red.result = is_fully_quoted(red.first_token);
	return (free(red.first_token), red.result);
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
