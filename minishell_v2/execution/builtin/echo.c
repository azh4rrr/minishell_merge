/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:06:47 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/08 23:16:58 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_n(char *parm)
{
	int	i;

	i = 0;
	if (parm[i] == '-')
		i++;
	while (parm[i] == 'n')
		i++;
	if (parm[i] == '\0' && i >= 2)
		return (true);
	return (false);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	ck;

	i = 1;
	ck = 0;
	while (cmd[i] && check_n(cmd[i]))
	{
		ck = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (ck == 1)
		return (0);
	printf("\n");
	return (0);
}
