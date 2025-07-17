/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:24:41 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/17 10:03:31 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd_list(t_cmd *token)
{
	t_cmd	*next;

	while (token)
	{
		next = token->next;
		free_cmd_node(token);
		token = next;
	}
}

int	process_line(char *line, t_cmd **token_ptr)
{
	if (ft_strlen(line) <= 0)
		return (0);
	add_history(line);
	*token_ptr = tokenization(line);
	return (0);
}

int	parse_commands(char *line, t_shell *var)
{
	if (process_line(line, &var->list) != 0)
		return (1);
	if (syntax_error(line))
		return (free_cmd_list(var->list), 1);
	if (var->list)
		return (expand_cmd_list(var->list, var), 0);
	else
		return (free(line), 1);
}
