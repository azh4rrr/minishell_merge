/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:58:48 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 00:15:40 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**build_environment_array(t_list *list)
{
	int		len;
	t_list	*tmp;
	int		i;
	char	*join;
	char	**env;

	i = 0;
	len = list_size(list);
	tmp = list;
	env = malloc(sizeof (char *) * (len + 1));
	if (!env)
		error_message(errno, NULL);
	while (tmp)
	{
		if (tmp->eg)
			join = ft_strjoin(tmp->key, "=");
		else
			join = ft_strdup(tmp->key);
		env[i++] = ft_strjoin(join, tmp->value);
		if (join)
			free(join);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	*add_shlvl(char *value)
{
	int	nm;

	nm = ft_atoi(value) + 1;
	return (ft_itoa(nm));
}

void	add_default_env(t_list **list)
{
	char	*pwd;

	pwd = NULL;
	if (!get_value(*list, "SHLVL"))
		list_add_back(list, list_new_node("1", "SHLVL", true));
	if (!get_value(*list, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		list_add_back(list, list_new_node(pwd, "PWD", true));
		free(pwd);
	}
	if (!get_value(*list, "_"))
		list_add_back(list, list_new_node("/usr/bin/env", "_", true));
	if (!get_value(*list, "OLDPWD"))
		list_add_back(list, list_new_node("", "OLDPWD", false));
}
