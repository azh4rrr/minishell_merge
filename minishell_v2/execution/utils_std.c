/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:49:58 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 00:56:05 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	init_shell_fds(t_shell *shell)
{
	shell->std_backup[0] = dup(STDIN_FILENO);
	shell->std_backup[1] = dup(STDOUT_FILENO);
	if (shell->std_backup[0] == -1 || shell->std_backup[1] == -1)
		return (strerror(errno), false);
	return (true);
}

void	cleanup_shell_fds(t_shell *shell)
{
	close(shell->std_backup[0]);
	close(shell->std_backup[1]);
}

bool	restore_standard_input(t_shell *shell)
{
	if (dup2(shell->std_backup[0], STDIN_FILENO) == -1)
		return (strerror(errno), false);
	if (dup2(shell->std_backup[1], STDOUT_FILENO) == -1)
		return (strerror(errno), false);
	return (true);
}
