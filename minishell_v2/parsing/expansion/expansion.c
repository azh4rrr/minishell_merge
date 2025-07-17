/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:00:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/17 12:30:23 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_expand(t_exp *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->in_single = 0;
	exp->in_double = 0;
	exp->var_len = 0;
	exp->expanded = NULL;
	exp->var_name = NULL;
	exp->result = NULL;
}

char	*get_env_value(t_list *env, char *key)
{
	t_list	*current;
	int		key_len;

	current = env;
	key_len = ft_strlen(key);
	while (current)
	{
		if (current->key && ft_strlen(current->key) == key_len
			&& ft_strncmp(current->key, key, key_len) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	get_var_len(char *str, int start)
{
	int	len;

	len = 0;
	if (str[start] == '$')
	{
		if (ft_isalpha(str[start + 1]) || str[start + 1] == '_' || str[start + 1] == '@')
		{
			len = 1;
			while ((str[start + len] )&& (ft_isalnum(str[start + len])
					|| str[start + len] == '_' || str[start + len] == '@'))
				len++;
		}
	}
	return (len);
}

char	*extract_var_name(char *str, int start, int len)
{
	char	*var_name;

	if (len <= 1)
		return (NULL);
	var_name = ft_substr(str, start + 1, len - 1);
	return (var_name);
}

void	expand_cmd_list(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*current;

	if (!cmd_list || !shell)
		return ;
	current = cmd_list;
	while (current)
	{
		expand_cmd_array(current->cmd, shell);
		expand_redirection_list(current->redirec, shell);
		remove_quotes_from_cmd_array(current->cmd);
		remove_quotes_from_redirection_list(current->redirec);
		current = current->next;
	}
}
