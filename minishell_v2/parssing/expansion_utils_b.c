/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:10:11 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/14 15:22:37 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expanded_value(char *var_name, t_shell *shell)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	value = get_env_value(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

void	remove_quotes_from_cmd_array(char **cmd)
{
	int		i;
	char	*unquoted;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		unquoted = remove_quotes(cmd[i]);
		if (unquoted)
		{
			free(cmd[i]);
			cmd[i] = unquoted;
		}
		i++;
	}
}

void	remove_quotes_from_redirection_list(t_redirec *redirec)
{
	t_redirec	*current;
	char		*unquoted;

	if (!redirec)
		return ;
	current = redirec;
	while (current)
	{
		unquoted = remove_quotes(current->name);
		if (unquoted)
		{
			free(current->name);
			current->name = unquoted;
		}
		current = current->next;
	}
}
