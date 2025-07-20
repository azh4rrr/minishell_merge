/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:50:24 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 18:30:24 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redir(char *line)
{
	int		i;
	char	**cmd;

	if (is_fully_quoted(line))
		return (0);
	i = 0;
	cmd = tokenize_with_redirections(line);
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (!redire_check(cmd[i]) && !cmd[i + 1])
			return (printf("minishell: syntax error"
					"near unexpected token `newline'\n"),
				free_cmd_array(cmd),
				1);
		if (!redire_check(cmd[i]) && !redire_check(cmd[i + 1]))
			return (printf("minishell: syntax error"
					"near unexpected token `%s'\n",
					cmd[i + 1]),
				free_cmd_array(cmd),
				1);
		i++;
	}
	return (free_cmd_array(cmd), 0);
}

static void	handle_special_char(char *cmd_str, char *temp_cmd, int *i, int *j)
{
	if (*i > 0 && cmd_str[*i - 1] != ' ')
		temp_cmd[(*j)++] = ' ';
	temp_cmd[(*j)++] = cmd_str[(*i)++];
	if (cmd_str[*i] && is_redir_char(cmd_str[*i]) && cmd_str[*i] == cmd_str[*i
			- 1])
		temp_cmd[(*j)++] = cmd_str[(*i)++];
	if (cmd_str[*i] && (cmd_str[*i - 1] == '|' || is_redir_char(cmd_str[*i
					- 1])))
		temp_cmd[(*j)++] = ' ';
	if (cmd_str[*i] && cmd_str[*i] == '|')
		temp_cmd[(*j)++] = cmd_str[(*i)++];
	if (cmd_str[*i] && cmd_str[*i] != ' ')
		temp_cmd[(*j)++] = ' ';
}

char	**tokenize_pipe(char *cmd_str)
{
	char	**tokens;
	char	*temp_cmd;
	int		i;
	int		j;

	temp_cmd = malloc(ft_strlen(cmd_str) * 4 + 1);
	if (!temp_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_str[i])
	{
		if ((is_redir_char(cmd_str[i]) || cmd_str[i] == '|')
			&& !is_inside_quotes(cmd_str, i))
			handle_special_char(cmd_str, temp_cmd, &i, &j);
		else
			temp_cmd[j++] = cmd_str[i++];
	}
	temp_cmd[j] = '\0';
	tokens = quote_aware_split(temp_cmd, ' ');
	free(temp_cmd);
	return (tokens);
}

int	handle_pipe(char *line)
{
	int		i;
	char	**tokens;

	if (is_fully_quoted(line))
		return (0);
	tokens = tokenize_pipe(line);
	if (!tokens)
		return (1);
	i = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 1))
		{
			if (i == 0 || !ft_strncmp(tokens[i + 1], "|", 1) || !tokens[i + 1])
				return (free_cmd_array(tokens), 1);
			if (!redire_check(tokens[i - 1]))
				return (free_cmd_array(tokens), 1);
		}
		i++;
	}
	free_cmd_array(tokens);
	return (0);
}

int	syntax_error(char *line)
{
	if (handle_pipe(line))
		return (printf("minishell: syntax error near unexpected token `|'\n"),
			1);
	if (handle_quotes(line))
		return (printf("minishell: quoting error\n"), 1);
	if (handle_redir(line))
		return (1);
	return (0);
}
