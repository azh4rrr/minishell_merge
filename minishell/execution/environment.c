/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:11:01 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 23:52:46 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_value_key(char *line, char **key, char **value)
{
	int	i;

	i = 0;
	*key = NULL;
	*value = NULL;
	if (!line || !*line)
		return ;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=')
	{
		*key = ft_substr(line, 0, i);
		*value = ft_strdup(line + i + 1);
	}
	else
		*key = ft_substr(line, 0, i);
}

t_list	*check_and_create_env_node(char *key, char *value)
{
	char	*shell_lvl;
	t_list	*new;

	if (!ft_strcmp(key, "OLDPWD"))
		new = list_new_node("", key, false);
	else if (!ft_strcmp(key, "SHLVL"))
	{
		shell_lvl = add_shlvl(value);
		new = list_new_node(shell_lvl, key, true);
		free(shell_lvl);
	}
	else
		new = list_new_node(value, key, true);
	return (new);
}

t_list	*set_env(char **env)
{
	t_list	*list;
	t_list	*new;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	list = NULL;
	while (env[i])
	{
		set_value_key(env[i], &key, &value);
		new = check_and_create_env_node(key, value);
		list_add_back(&list, new);
		if (key)
			free(key);
		if (value)
			free(value);
		i++;
	}
	return (list);
}

t_list	*environment(char **env)
{
	t_list	*list;

	list = NULL;
	if (!env || !*env)
		add_default_env(&list);
	else
	{
		list = set_env(env);
		add_default_env(&list);
	}
	return (list);
}
