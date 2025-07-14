/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:24:27 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/08 23:13:42 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	status_scan(int *status)
{
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
		{
			write(1, "\n", 1);
			return (130);
		}
		else if (WTERMSIG(*status) == SIGQUIT)
		{
			write(1, "Quit: 3\n", 8);
			return (131);
		}
	}
	return (0);
}

bool	wait_and_exit(int last_pid)
{
	int	status;
	int	pid;

	pid = 1;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == -1)
			continue ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (exit_status == 1)
					return (true);
			}
			else if (WIFSIGNALED(status))
			{
				exit_status = status_scan(&status);
			}
		}
	}
	return (false);
}
