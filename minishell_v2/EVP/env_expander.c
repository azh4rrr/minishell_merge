/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:04:33 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/14 18:33:22 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_value(char *key, t_list *env)
{
	t_list	*tmp;
	char	*value;

	tmp = env;
	value = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		value = ft_strdup(tmp->value);
	return (value);
}

char	*key_not_found(char **content, int pos_key, int len_key)
{
	char	*value;
	int		r;
	int		f;

	r = -1;
	f = 0;
	value = malloc(sizeof(char) * (ft_strlen(*content) - len_key + 2));
	if (!value)
		return (errput(ERR_MEM), NULL);
	while ((*content)[++r])
	{
		if (r == pos_key)
		{
			r += len_key;
			continue ;
		}
		value[f++] = (*content)[r];
	}
	value[f] = '\0';
	free(*content);
	return (value);
}

char	*key_value(char **content, char *v_env, int pos, int len_key)
{
	char	*value;
	int		r;
	int		g;
	int		f;

	r = -1;
	g = -1;
	f = 0;
	value = malloc(ft_strlen(*content) - len_key + ft_strlen(v_env) + 1);
	if (!value)
		return (errput(ERR_MEM), NULL);
	while ((*content)[++r] && r < ft_strlen(*content))
	{
		if (r == pos)
		{
			while (v_env[++g])
				value[f++] = v_env[g];
			r += len_key - 1;
			continue ;
		}
		value[f++] = (*content)[r];
	}
	value[f] = '\0';
	free(*content);
	return (value);
}
