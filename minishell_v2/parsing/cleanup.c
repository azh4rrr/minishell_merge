/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:21:53 by azhar             #+#    #+#             */
/*   Updated: 2025/07/20 15:39:18 by azhar            ###   ########.fr       */
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

void	free_redirec_list(t_redirec *head)
{
	t_redirec	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp);
	}
}

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
	cmds = NULL;
	return (1);
}

void	free_cmd_node(t_cmd *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (node->cmd && node->cmd[i])
		free(node->cmd[i++]);
	if (node->cmd)
		free(node->cmd);
	if (node->redirec)
		free_redirec_list(node->redirec);
	free(node);
}

void	cleanup_tokens(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
