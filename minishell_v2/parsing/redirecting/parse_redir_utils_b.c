/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:38:09 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 18:15:03 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_redire_char(char *cmd_str, char *temp_cmd, int *i, int *j)
{
	if (*i > 0 && cmd_str[*i - 1] != ' ')
		temp_cmd[(*j)++] = ' ';
	temp_cmd[(*j)++] = cmd_str[(*i)++];
	if (cmd_str[*i] && is_redir_char(cmd_str[*i])
		&& cmd_str[*i] == cmd_str[*i - 1])
		temp_cmd[(*j)++] = cmd_str[(*i)++];
	if (cmd_str[*i] && cmd_str[*i] != ' ')
		temp_cmd[(*j)++] = ' ';
}

char	*insert_space_around_redirection(char *cmd_str)
{
	char	*temp_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp_cmd = malloc(ft_strlen(cmd_str) * 3 + 1);
	if (!temp_cmd)
		return (NULL);
	while (cmd_str[i])
	{
		if (is_redir_char(cmd_str[i]) && !is_inside_quotes(cmd_str, i))
			handle_redire_char(cmd_str, temp_cmd, &i, &j);
		else
			temp_cmd[j++] = cmd_str[i++];
	}
	temp_cmd[j] = '\0';
	return (temp_cmd);
}

char	**tokenize_with_redirections(char *cmd_str)
{
	char	**tokens;
	char	*temp_cmd;

	temp_cmd = insert_space_around_redirection(cmd_str);
	if (!temp_cmd)
		return (NULL);
	tokens = quote_aware_split(temp_cmd, ' ');
	free(temp_cmd);
	return (tokens);
}

static char	*append_token_to_cmd(char *cmd, char *token)
{
	char	*temp;
	char	*new_cmd;

	if (cmd[0] != '\0')
	{
		temp = ft_strjoin(cmd, " ");
		free(cmd);
		if (!temp)
			return (NULL);
		new_cmd = ft_strjoin(temp, token);
		free(temp);
	}
	else
	{
		new_cmd = ft_strjoin(cmd, token);
		free(cmd);
	}
	return (new_cmd);
}

char	*build_cmd_string(char **tokens, int token_count)
{
	char	*new_cmd;
	int		i;

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
			new_cmd = append_token_to_cmd(new_cmd, tokens[i++]);
			if (!new_cmd)
				return (NULL);
		}
	}
	return (new_cmd);
}
