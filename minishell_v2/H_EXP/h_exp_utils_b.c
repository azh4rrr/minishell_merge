/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exp_utils_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:14:47 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 19:55:01 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quoted_h(char *s)
{
	if (ft_strchr(s, '\''))
		return (1);
	if (ft_strchr(s, '"'))
		return (2);
	return (0);
}

char	*add_quotes_h(char *s)
{
	char	*d;
	size_t	len;
	int		quote_type;

	if (!s)
		return (NULL);
	quote_type = quoted_h(s);
	len = ft_strlen(s);
	d = malloc(len + 3);
	if (!d || quote_type == 0)
		return (NULL);
	if (quote_type == 1)
	{
		d[0] = '"';
		ft_strncpy(d + 1, s, len);
		d[len + 1] = '"';
	}
	else if (quote_type == 2)
	{
		d[0] = '\'';
		ft_strncpy(d + 1, s, len);
		d[len + 1] = '\'';
	}
	d[len + 2] = '\0';
	return (d);
}

char	*get_expanded_value(char *var_name, t_shell *shell)
{
	char	*value;
	char	*quot_s;

	quot_s = NULL;
	if (!var_name)
		return (ft_strdup(""));
	value = get_env_value(shell->env, var_name);
	quot_s = add_quotes_h(value);
	if (quot_s)
		return (quot_s);
	else if (value)
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
