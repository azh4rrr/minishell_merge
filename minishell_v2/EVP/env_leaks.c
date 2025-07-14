/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_leaks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:07:41 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/14 18:37:04 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_leaks(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		p1char(&env->key);
		p1char(&env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	errput(char *s)
{
	write(2, s, ft_strlen(s));
}

void	p1char(char **ptr)
{
	if (!*ptr || !ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}