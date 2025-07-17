/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:19:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/17 09:24:36 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		exit_status;

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_shell	*var;

	var = malloc(sizeof(t_shell));
	init_shell_fds(var);
	(void)av;
	if (ac != 1)
		return (1);
	var->env = set_env(env);
	exit_status = 0;
	while (1)
	{
		set_signals_main();
		var->list = NULL;
		line = readline("minishell> ");
		if (!line)
			exit(0);
		if (parse_commands(line, var) != 0)
			continue ;
		execute_commands(var);
		free_cmd_list(var->list);
	}
}
