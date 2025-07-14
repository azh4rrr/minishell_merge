/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:33:23 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 01:03:37 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_list *list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	list_add_back(t_list **list, t_list *new)
{
	t_list	*tmp;

	if (!list)
		return ;
	if (!(*list))
	{
		(*list) = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*list_new_node(char *value, char *key, bool eg)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (error_message(errno, NULL), NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup (value);
	new->eg = eg;
	new->next = NULL;
	return (new);
}
