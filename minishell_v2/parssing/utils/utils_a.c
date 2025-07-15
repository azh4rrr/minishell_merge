/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:40:04 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/15 16:23:10 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_cmd_array(char **cmds)
{
	int	i;

	if (!cmds || !*cmds)
		return (1);
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = 	NULL; // Set cmds to NULL after freeing
	return (1);
}

int	allocate_token(t_cmd **token, char **cmds)
{
	int	i;

	*token = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*token)
	{
		i = 0;
		while (cmds[i])
			free(cmds[i++]);
		free(cmds);
		return (1);
	}
	(*token)->cmd = NULL;
	(*token)->redirec = NULL;
	(*token)->next = NULL;
	(*token)->prev = NULL; // Initialize prev pointer
	return (0);
}

int	setup_cmd_struct(t_cmd *current, char *cmd_str)
{
	if (!current || !cmd_str)
		return (1);
	current->cmd = ft_split(cmd_str, ' ');
	if (!current->cmd)
		return (1);
	current->redirec = NULL;
	return (0);
}

int	create_next_node(t_cmd *current, int has_next)
{
	if (!current)
		return (1);
	if (has_next)
	{
		current->next = (t_cmd *)malloc(sizeof(t_cmd));
		if (!current->next)
			return (1);
		current->next->cmd = NULL;
		current->next->redirec = NULL;
		current->next->next = NULL;
		current->next->prev = current; // Set backward link
	}
	else
		current->next = NULL;
	return (0);
}

t_cmd	*get_first_cmd(t_cmd *node)
{
	if (!node)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}
