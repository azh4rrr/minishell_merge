/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:51:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/08 23:10:35 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_if_exist_path(t_shell *val, t_cmd *cmd)
{
	char	**full_path;

	full_path = NULL;
	if (ft_strchr(cmd->cmd[0], '/'))
	{
		if (!access(cmd->cmd[0], X_OK))
			return (ft_strdup(cmd->cmd[0]));
		if (access(cmd->cmd[0], F_OK))
			error_message(errno, cmd->cmd[0]);
		return (NULL);
	}
	full_path = get_system_paths(val->env);
	if (!full_path)
	{
		if (!access(cmd->cmd[0], X_OK))
			return (ft_strdup(cmd->cmd[0]));
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->cmd[0], 2);
			return (ft_putstr_fd(": No such file or directory\n", 2), NULL);
		}
	}
	return (get_executable_paths(full_path, cmd->cmd[0]));
}

void	child_process(t_shell *val, t_cmd *cmd)
{
	char	*path;
	char	**env;

	path = NULL;
	env = NULL;
	if (!handle_redirections(cmd))
		exit(1);
	if (!setup_pipes(cmd))
		exit(1);
	if (!duplicate_standard_fds(cmd))
		exit(1);
	cleanup_shell_fds(val);
	if (is_builtin(cmd->cmd[0]))
		return (execute_builtin(cmd->cmd, val), exit(0));
	else
	{
		path = check_if_exist_path(val, cmd);
		if (!path)
			exit(127);
		env = build_environment_array(val->env);
		if (execve(path, cmd->cmd, env) == -1)
			return (error_message(errno, cmd->cmd[0]),
				free(path), p2char(&env), exit(1));
	}
}

void	parent_process(t_cmd *cmd)
{
	if (cmd->fd_pip[1] > 0)
		close(cmd->fd_pip[1]);
	if (cmd->fd_herdoc[0] > 0)
		close(cmd->fd_herdoc[0]);
	if (cmd->prev)
	{
		if (cmd->prev->fd_pip[0] > 0)
		{
			close(cmd->prev->fd_pip[0]);
			cmd->prev->fd_pip[0] = -1;
		}
		if (cmd->prev->prev)
		{
			if (cmd->prev->prev->fd_pip[0] > 0)
			{
				close(cmd->prev->prev->fd_pip[0]);
				cmd->prev->prev->fd_pip[0] = -1;
			}
		}
	}
}

void	execute_with_fork(t_shell *val)
{
	t_cmd	*list;
	int		fork_pid;

	list = val->list;
	while (list)
	{
		if (list->next)
		{
			if (pipe(list->fd_pip) == -1)
				return ;
		}
		fork_pid = fork();
		if (fork_pid < 0)
			perror(FORK_FAILD);
		if (fork_pid == 0)
		{
			set_signals_child();
			child_process(val, list);
		}
		if (fork_pid > 0)
			parent_process(list);
		restore_standard_input(val);
		list = list->next;
	}
	wait_and_exit(fork_pid);
}
