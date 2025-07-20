/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:00:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 15:40:14 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirec	*create_redirec_node(char *name, t_type type)
{
	t_redirec	*new;

	new = (t_redirec *)malloc(sizeof(t_redirec));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_redirec_node(t_redirec **head, t_redirec *new)
{
	t_redirec	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	has_quotes_in_delimiter(char *delimiter)
{
	int	i;

	if (!delimiter)
		return (0);
	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	check_redirection_type(char **str, int i)
{
	if (!str[i] || !*str[i])
		return (0);
	if (str[i][0] == '>' && str[i][1] == '\0')
		return (1);
	else if (str[i][0] == '>' && str[i][1] == '>' && str[i][2] == '\0')
		return (2);
	else if (str[i][0] == '<' && str[i][1] == '\0')
		return (3);
	else if (str[i][0] == '<' && str[i][1] == '<' && str[i][2] == '\0')
	{
		if (!str[i + 1])
			return (0);
		if (has_quotes_in_delimiter(str[i + 1]))
			return (5);
		else
			return (4);
	}
	return (0);
}
