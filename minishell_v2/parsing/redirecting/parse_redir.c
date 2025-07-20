/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:52:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 14:57:32 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirec	*create_appropriate_redirection_node(char *filename, int redir_type)
{
	if (!filename)
		return (NULL);
	if (redir_type == 1)
		return (create_redirec_node(filename, D_OUTFILE));
	else if (redir_type == 2)
		return (create_redirec_node(filename, D_APPEND));
	else if (redir_type == 3)
		return (create_redirec_node(filename, D_INFILE));
	else if (redir_type == 4)
		return (create_redirec_node(filename, D_HERDOC));
	else if (redir_type == 5)
		return (create_redirec_node(filename, D_HERDOC_Q));
	return (NULL);
}

int	add_redirections(char **tokens, t_redirec **redirec_list)
{
	int			i;
	t_redirec	*new_node;
	int			redir_type;

	i = 0;
	while (tokens[i])
	{
		redir_type = check_redirection_type(tokens, i);
		if (redir_type > 0 && tokens[i + 1])
		{
			new_node = create_appropriate_redirection_node(tokens[i + 1],
					redir_type);
			if (!new_node)
				return (1);
			add_redirec_node(redirec_list, new_node);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}

char	*parse_redirections(char *cmd_str, t_redirec **redirec_list)
{
	char	**tokens;
	char	*new_cmd;

	tokens = tokenize_with_redirections(cmd_str);
	if (!tokens)
		return (NULL);
	new_cmd = build_cmd_string(tokens, count_valid_tokens(tokens));
	if (!new_cmd)
		return (free_cmd_array(tokens), NULL);
	if (add_redirections(tokens, redirec_list))
		free_cmd_array(tokens);
	return (new_cmd);
}

int	process_special_cmd_cases(t_cmd *current, char *cmd_str)
{
	if (first_token_is_fully_quoted(cmd_str))
	{
		current->cmd = quote_aware_split(cmd_str, ' ');
		if (!current->cmd)
			return (1);
		return (0);
	}
	else if (contains_only_quotes_and_spaces(cmd_str))
	{
		current->cmd = malloc(sizeof(char *) * 2);
		if (!current->cmd)
			return (1);
		current->cmd[0] = ft_strdup(cmd_str);
		if (!current->cmd[0])
			return (free(current->cmd), 1);
		current->cmd[1] = NULL;
		return (0);
	}
	return (-1);
}

int	setup_cmd_struct_with_redirection(t_cmd *current, char *cmd_str)
{
	char	*processed_cmd;
	int		special_case_result;

	if (!current || !cmd_str)
		return (1);
	current->redirec = NULL;
	special_case_result = process_special_cmd_cases(current, cmd_str);
	if (special_case_result == 0)
		return (0);
	else if (special_case_result == -1)
	{
		processed_cmd = parse_redirections(cmd_str, &(current->redirec));
		if (!processed_cmd)
			return (1);
		current->cmd = quote_aware_split(processed_cmd, ' ');
		free(processed_cmd);
		if (!current->cmd)
			return (1);
	}
	return (0);
}
