/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:22:28 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/15 17:21:19 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_expane(t_list *env, char *line, int fd)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			j = i + 1;
			while (line[j] && (ft_isalnum(line[j]) || line[j] == '_')) // $@ // $+ // $"USER"
				j++;
			// if (j == i + 1)
			key = ft_substr(line, i + 1, j - (i + 1));
			value = get_value(env, key);
			if (key)
				free(key);
			if (value)
				ft_putstr_fd(value, fd);
			i = j;
		}
		if (line[i] != '\0')
			write(fd, &line[i], 1);  
		i++;
	}
}

void	herdoc_read(t_list *env, t_cmd *tmp, char *dlm, t_type expand)
{
	char	*line;

	dlm = ft_strjoin(dlm, "\n");
	if (!dlm)
		return ;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strcmp(line, dlm))
			break ;
		if (expand == D_HERDOC_Q)
			ft_putstr_fd(line, tmp->fd_herdoc[1]);
		else
			ft_putstr_expane(env, line, tmp->fd_herdoc[1]);  
		// resolve_heredoc(env, &line, tmp->fd_herdoc[1]);
		free(line);
	}
	if (line)
		free(line);
	free(dlm);
	close(tmp->fd_herdoc[0]);
	close(tmp->fd_herdoc[1]);
}

bool	fork_and_handle_heredoc(t_shell *shell, t_cmd *tmp, char *delimiter,
		t_type expand)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid < 0)
	{
		close_fd(&tmp->fd_herdoc[0]);
		close_fd(&tmp->fd_herdoc[1]);
		return (error_message(errno, NULL), false);
	}
	if (fork_pid == 0)
	{
		signal(SIGINT, signal_herdoc);
		herdoc_read(shell->env, tmp, delimiter, expand);
		free_cmd_list(tmp);
		free_list(&shell->env);
		exit(0);
	}
	if (fork_pid > 0)
	{
		if (wait_and_exit(fork_pid))
			return (false);
		close_fd(&tmp->fd_herdoc[1]);
	}
	return (true);
}

bool	process_heredocs(t_shell *val)
{
	t_cmd		*tmp;
	t_redirec	*redc;

	tmp = val->list;
	initialize_command_fds(tmp);
	while (tmp)
	{
		redc = tmp->redirec;
		while (redc)
		{
			if (redc->type == D_HERDOC || redc->type == D_HERDOC_Q)
			{
				if (tmp->fd_herdoc[0] > 0)
					close_fd(&tmp->fd_herdoc[0]);
				if (pipe(tmp->fd_herdoc) == -1)
					return (strerror(errno), false);
				if (!fork_and_handle_heredoc(val, tmp, redc->name, redc->type))
					return (close_fd(&tmp->fd_herdoc[0]),
						close_fd(&tmp->fd_herdoc[1]), false);
			}
			redc = redc->next;
		}
		tmp = tmp->next;
	}
	return (true);
}
