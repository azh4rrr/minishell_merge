/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:26:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/09 00:20:32 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(t_list *env, char *key)
{
	t_list	*tmp;

	if (!env || !key)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_env(char *key, char *value, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->eg = true;
			return ;
		}
		tmp = tmp->next;
	}
	list_add_back(env, list_new_node(value, key, true));
}

char	*resolve_cd_path(char *str, t_list *env)
{
	char	*ret;

	if (str == NULL || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "~") == 0)
	{
		ret = get_value(env, "HOME");
		if (!ret)
			return (printf("cd: HOME not set\n"), NULL);
		return (ret);
	}
	else if (!ft_strcmp(str, "-"))
	{
		ret = get_value(env, "OLDPWD");
		if (!ret)
			return (printf("cd: OLDPWD not set\n"), NULL);
		return (ret);
	}
	else if (!ft_strncmp(str, "~/", 2))
	{
		ret = ft_strjoin(get_value(env, "HOME"), str + 1);
		return (ret);
	}
	else
		return (str);
}

int	ft_cd(t_list *env, char *path)
{
	char	*oldpwd;
	char	*p;

	oldpwd = getcwd(NULL, 0);
	p = resolve_cd_path(path, env);
	if (!oldpwd)
		return (error_message(errno, p), 1);
	if (chdir(p) == -1)
		return (free(oldpwd), error_message(errno, p), 1);
	if (!ft_strncmp(path, "~/", 2))
		free(p);
	p = getcwd(NULL, 0);
	if (!p)
		return (free(oldpwd), error_message(errno, p), 1);
	update_env("PWD", p, &env);
	update_env("OLDPWD", oldpwd, &env);
	free(p);
	free(oldpwd);
	return (0);
}
