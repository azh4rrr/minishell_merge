/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:38:12 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/14 18:29:07 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_shell(t_shell **shell)
{
	clear_all_pipes((*shell)->list);
	free_list(&(*shell)->env);
	free_cmd_list((*shell)->list);
	free(*shell);
	*shell = NULL;
}

void	free_list_node(t_list *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
	node = NULL;
}

void	free_list(t_list **head)
{
	t_list	*current;
	t_list	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free_list_node(current);
		current = next;
	}
	*head = NULL;
}
