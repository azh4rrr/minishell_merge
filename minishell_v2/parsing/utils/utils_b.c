/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:41:40 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 15:24:39 by azhar            ###   ########.fr       */
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
