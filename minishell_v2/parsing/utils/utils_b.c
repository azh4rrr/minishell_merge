/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:41:40 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 18:15:10 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	arg_create(t_cmd *token, char **cmds)
{
	t_cmd	*current;
	int		i;

	current = token;
	i = 0;
	while (cmds[i])
	{
		if (setup_cmd_struct_with_redirection(current, cmds[i]))
			return (1);
		if (create_next_node(current, cmds[i + 1] != NULL))
			return (1);
		if (cmds[i + 1])
			current = current->next;
		i++;
	}
	return (0);
}

t_cmd	*handle_token_error(char **cmds, t_cmd *token)
{
	int	i;

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
	free(token);
	return (NULL);
}

t_cmd	*tokenization(char *line)
{
	char	**cmds;
	t_cmd	*token;
	int		i;

	cmds = quote_aware_split(line, '|');
	if (!cmds)
		return (NULL);
	if (allocate_token(&token, cmds))
		return (NULL);
	if (arg_create(token, cmds))
		return (handle_token_error(cmds, token));
	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
	return (token);
}

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

int	count_valid_tokens(char **tokens)
{
	int	i;
	int	count;
	int	redir_type;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		redir_type = check_redirection_type(tokens, i);
		if (redir_type == 0)
			count++;
		else if (tokens[i + 1])
			i++;
		i++;
	}
	return (count);
}
