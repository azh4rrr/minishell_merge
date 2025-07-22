/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:17:44 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/08 23:10:55 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_command_fds(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		current->fd_herdoc[0] = -1;
		current->fd_herdoc[1] = -1;
		current->fd_io[0] = -1;
		current->fd_io[1] = -1;
		current->fd_pip[0] = -1;
		current->fd_pip[1] = -1;
		current = current->next;
	}
}

void	close_fd(int *fd)
{
	if (*fd > 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	clear_all_pipes(t_cmd *cmd)
{
	t_cmd	*current;

	if (!cmd)
		return ;
	current = cmd;
	while (current)
	{
		if (current->fd_pip[0] > 0)
			close(current->fd_pip[0]);
		if (current->fd_pip[1] > 0)
			close(current->fd_pip[1]);
		if (current->fd_herdoc[0] > 0)
			close(current->fd_herdoc[0]);
		if (current->fd_io[0] > 0)
			close(current->fd_io[0]);
		if (current->fd_io[1] > 0)
			close(current->fd_io[1]);
		current = current->next;
	}
}
