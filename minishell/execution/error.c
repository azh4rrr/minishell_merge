/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:04:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 00:24:21 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_error(int error_num, char *file_name)
{
	fprintf(stderr, ("minishell: "));
	if (error_num == EACCES)
		return (perror(file_name));
	if (error_num == ENOENT)
		return (perror(file_name));
	if (error_num == EEXIST)
		return (perror(file_name));
	if (error_num == EISDIR)
		return (perror(file_name));
	if (error_num == ENOTDIR)
		return (fprintf(stderr, ("cd: ")), perror(file_name));
}

void	error_message(int error_num, char *message)
{
	if (error_num == EACCES || error_num == ENOENT || error_num == EEXIST
		|| error_num == EISDIR || error_num == ENOTDIR)
		return (file_error(error_num, message));
	else if (error_num == ENOMEM)
		return (perror("minishell"));
	else if (error_num == EINVAL)
		return (perror("minishell"));
	else if (error_num == ENOSPC)
		return (perror("minishell"));
	else if (error_num == EIO)
		return (perror("minishell"));
	else if (error_num == EPIPE)
		return (perror("minishell"));
	else if (error_num == EROFS)
		return (perror("minishell"));
	else if (error_num == ELOOP)
		return (perror("minishell"));
	else
		fprintf(stderr, ("%s\n"), message);
}
