/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:52:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/07 17:01:50 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commands(t_shell *val)
{
	signal(SIGINT, SIG_IGN);
	if (!process_heredocs(val))
		return ;
	if (!init_shell_fds(val))
		return ;
	if (is_builtin(val->list->cmd[0]) && !val->list->next)
	{
		if (!handle_redirections(val->list))
			return (cleanup_shell_fds(val));
		if (!duplicate_standard_fds(val->list))
			return (cleanup_shell_fds(val), close_fd(&val->list->fd_herdoc[0]));
		execute_builtin(val->list->cmd, val);
		restore_standard_input(val);
	}
	else
		execute_with_fork(val);
	cleanup_shell_fds(val);
}
