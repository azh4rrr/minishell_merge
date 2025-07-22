/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:49:22 by macbookpro        #+#    #+#             */
/*   Updated: 2025/07/08 23:15:09 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_list *env)
{
	char	*pwd;

	pwd = get_value(env, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", pwd);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	print_env_list(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->eg == true)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	execute_builtin(char **cmd, t_shell *val)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		exit_status = ft_pwd(val->env);
	else if (ft_strcmp(cmd[0], "env") == 0)
		exit_status = print_env_list(val->env);
	else if (ft_strcmp(cmd[0], "export") == 0)
		exit_status = ft_export_variable(val, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		exit_status = ft_cd(val->env, cmd[1]);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		exit_status = ft_unset(val, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit_status = ft_exit(cmd, &val);
	else
		return ;
}
