/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:24:41 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 15:22:27 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
