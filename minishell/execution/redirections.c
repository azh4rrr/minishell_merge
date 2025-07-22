/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:45:30 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 01:02:40 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	setup_pipes(t_cmd *command)
{
	if (command->fd_io[1] != STDOUT_FILENO && command->fd_pip[1] > 0)
	{
		close(command->fd_pip[1]);
		command->fd_pip[1] = -1;
	}
	else if (command->fd_io[1] == STDOUT_FILENO
		&& command->next && command->fd_pip[1] > 0)
		command->fd_io[1] = command->fd_pip[1];
	if (command->prev && command->fd_io[0] == STDIN_FILENO)
		command->fd_io[0] = command->prev->fd_pip[0];
	if (command->fd_pip[0] > 0)
		close(command->fd_pip[0]);
	return (true);
}

bool	duplicate_standard_fds(t_cmd *cmd)
{
	if (cmd->fd_io[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
			return (close(cmd->fd_io[0]), error_message(errno, NULL), false);
		close(cmd->fd_io[0]);
	}
	if (cmd->fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_io[1], STDOUT_FILENO) == -1)
			return (close(cmd->fd_io[1]), error_message(errno, NULL), false);
		close(cmd->fd_io[1]);
	}
	return (true);
}

bool	set_input(t_cmd *command, t_redirec *in)
{
	if (command->fd_io[0] != STDIN_FILENO
		&& command->fd_io[0] != command->fd_herdoc[0])
		close(command->fd_io[0]);
	if (in->type == D_INFILE)
	{
		command->fd_io[0] = open(in->name, O_RDONLY, 0777);
		if (command->fd_io[0] == -1)
			return (error_message(errno, in->name), false);
	}
	else
		command->fd_io[0] = command->fd_herdoc[0];
	return (true);
}

bool	set_output(t_cmd *command, t_redirec *out)
{
	if (command->fd_io[1] != STDOUT_FILENO)
	{
		close(command->fd_io[1]);
		command->fd_io[1] = -1;
	}
	if (out->type == D_OUTFILE)
	{
		command->fd_io[1] = open(out->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (command->fd_io[1] == -1)
			return (error_message(errno, out->name), false);
	}
	else
	{
		command->fd_io[1] = open(out->name, O_CREAT | O_APPEND | O_RDWR, 0777);
		if (command->fd_io[1] == -1)
			return (error_message(errno, out->name), false);
	}
	return (true);
}

bool	handle_redirections(t_cmd *command)
{
	t_redirec	*tmp;

	tmp = command->redirec;
	command->fd_io[0] = STDIN_FILENO;
	command->fd_io[1] = STDOUT_FILENO;
	while (tmp)
	{
		if (tmp->type == D_INFILE || tmp->type == D_HERDOC
			|| tmp->type == D_HERDOC_Q)
			if (!set_input(command, tmp))
				return (false);
		if (tmp->type == D_OUTFILE || tmp->type == D_APPEND)
			if (!set_output(command, tmp))
				return (false);
		tmp = tmp->next;
	}
	if (command->fd_io[0] != command->fd_herdoc[0])
	{
		close(command->fd_herdoc[0]);
		command->fd_herdoc[0] = -1;
	}
	return (true);
}
