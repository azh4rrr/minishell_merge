/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:38:09 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/15 11:38:25 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(char *token)
{
	char	*result;
	int		i;
	int		j;
	char	current_quote;

	i = 0;
	j = 0;
	current_quote = 0;
	if (!token)
		return (NULL);
	result = malloc(ft_strlen(token) + 1);
	if (!result)
		return (NULL);
	while (token[i])
	{
		if (!current_quote && (token[i] == '\'' || token[i] == '"'))
			current_quote = token[i];
		else if (current_quote && token[i] == current_quote)
			current_quote = 0;
		else
			result[j++] = token[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	**tokenize_with_redirections(char *cmd_str)
{
	char	**tokens;
	char	*temp_cmd;
	int		i;
	int		j;

	temp_cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd_str) * 3 + 1));
	if (!temp_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_str[i])
	{
		if (is_redir_char(cmd_str[i]) && !is_inside_quotes(cmd_str, i))
		{
			if (i > 0 && cmd_str[i - 1] != ' ')
				temp_cmd[j++] = ' ';
			temp_cmd[j++] = cmd_str[i++];
			if (cmd_str[i] && is_redir_char(cmd_str[i])
				&& cmd_str[i] == cmd_str[i - 1])
				temp_cmd[j++] = cmd_str[i++];
			if (cmd_str[i] && cmd_str[i] != ' ')
				temp_cmd[j++] = ' ';
		}
		else
			temp_cmd[j++] = cmd_str[i++];
	}
	temp_cmd[j] = '\0';
	tokens = quote_aware_split(temp_cmd, ' ');
	free(temp_cmd);
	return (tokens);
}

int	count_valid_tokens(char **tokens)
{
	int	i;
	int	count;
	int	redir_type;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		redir_type = check_redirection_type(tokens , i);
		if (redir_type == 0)
			count++;
		else if (tokens[i + 1])
			i++;
		i++;
	}
	return (count);
}

char	*build_cmd_string(char **tokens, int token_count)
{
	char *new_cmd;
	char *temp;
	int i;

	if (token_count == 0)
		return (ft_strdup(""));
	new_cmd = ft_strdup("");
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (check_redirection_type(tokens, i) > 0 && tokens[i + 1])
			i += 2;
		else
		{
			if (new_cmd[0] != '\0')
			{
				temp = ft_strjoin(new_cmd, " ");
				free(new_cmd);
				if (!temp)
					return (NULL);
				new_cmd = temp;
			}
			temp = ft_strjoin(new_cmd, tokens[i++]);
			free(new_cmd);
			if (!temp)
				return (NULL);
			new_cmd = temp;
		}
	}
	return (new_cmd);
}
