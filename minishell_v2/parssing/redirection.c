/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:00:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/05/28 17:54:46 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_redirection_type(const char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == '>' && (!str[1] || str[1] != '>'))
		return (1);
	else if (str[0] == '>' && str[1] == '>')
		return (2);
	else if (str[0] == '<' && (!str[1] || str[1] != '<'))
		return (3);
	else if (str[0] == '<' && str[1] == '<')
		return (4);
	return (0);
}

void	print_redirec_list(t_redirec *head)
{
	t_redirec *current;
	const char *type_str[4] = {COLORE_RED "OUTPUT" COLORE_RESET,
		COLORE_YELLOW "APPEND" COLORE_RESET, COLORE_BLUE "INPUT" COLORE_RESET,
		COLORE_MAGENTA "HEREDOC" COLORE_RESET};

	current = head;
	while (current)
	{
		printf(COLORE_GREEN "REDIRECTION:" COLORE_RESET " [" COLORE_CYAN "%s" COLORE_RESET "] Type:"
							"%s\n",
				current->name,
				type_str[current->type]);
		current = current->next;
	}
}