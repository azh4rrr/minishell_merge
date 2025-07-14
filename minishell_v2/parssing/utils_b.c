/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:41:40 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/06/14 18:46:37 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_create(t_cmd *token, char **cmds)
{
	t_cmd	*current;
	int		i;

	current = token;
	i = 0;
	while (cmds[i])
	{
		if (setup_cmd_struct_with_redirection(current, cmds[i]))
			return (1);
		if (create_next_node(current, cmds[i + 1] != NULL))
			return (1);
		if (cmds[i + 1])
			current = current->next;
		i++;
	}
	return (0);
}

t_cmd	*handle_token_error(char **cmds, t_cmd *token)
{
	int	i;

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
	free(token);
	return (NULL);
}

t_cmd	*tokenization(char *line)
{
	char	**cmds;
	t_cmd	*token;
	int		i;

	// Use quote-aware split for pipe separation
	cmds = quote_aware_split(line, '|');
	if (!cmds)
		return (NULL);
	if (allocate_token(&token, cmds))
		return (NULL);
	if (arg_create(token, cmds))
		return (handle_token_error(cmds, token));
	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
	return (token);
}

void	print_cmd_list(t_cmd *token)
{
	t_cmd	*tmp;
	int		i;

	tmp = token;
	while (tmp)
	{
		i = 0;
		printf(COLORE_GREEN "COMMAND:" COLORE_RESET " ");
		while (tmp->cmd && tmp->cmd[i])
			printf("[" COLORE_CYAN "%s" COLORE_RESET "]", tmp->cmd[i++]);
		printf("\n");
		if (tmp->redirec)
			print_redirec_list(tmp->redirec);
		tmp = tmp->next;
	}
}

void	free_cmd_node(t_cmd *node)
{
	int i;

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