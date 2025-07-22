/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:38:23 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/08 19:06:08 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env_node(t_shell *val, t_list *curr)
{
	t_list	*prev;

	prev = val->env;
	if (curr == val->env)
	{
		val->env = curr->next;
		free_list_node(curr);
		return ;
	}
	while (prev && prev->next != curr)
		prev = prev->next;
	if (prev)
	{
		prev->next = curr->next;
		free_list_node(curr);
	}
}

int	ft_unset(t_shell *val, char **cmd)
{
	int		j;
	t_list	*curr;

	j = 1;
	while (cmd[j])
	{
		curr = val->env;
		while (curr)
		{
			if (!ft_strcmp(cmd[j], curr->key))
				remove_env_node(val, curr);
			curr = curr->next;
		}
		j++;
	}
	return (0);
}
