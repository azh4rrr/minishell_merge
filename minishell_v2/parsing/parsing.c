/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:24:41 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 23:04:15 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(char *line, t_shell *var)
{
	char	*pre_line;
	int		status;

	pre_line = pre_expand_line_if_needed(line, var);
	status = parse_commands(pre_line, var);
	free(pre_line);
	return (status);
}

int	handle_quotes(char *line)
{
	int		i;
	char	qt;
	int		fl;

	i = 0;
	fl = 1;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			qt = line[i];
			i = i + 1;
			while (line[i] != qt && line[i])
				i++;
			if (line[i] != qt)
				fl = 0;
			if (line[i] == qt)
				i++;
		}
		else
			i++;
	}
	if (fl == 0)
		return (1);
	return (0);
}

int	redire_check(char *line)
{
	if (!ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
		return (0);
	else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1))
		return (0);
	return (1);
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
