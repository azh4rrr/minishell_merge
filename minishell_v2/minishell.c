/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:19:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/15 17:31:19 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		exit_status;

void	free_cmd_list(t_cmd *token)
{
	t_cmd	*next;

	while (token)
	{
		next = token->next;
		free_cmd_node(token);
		token = next;
	}
}

int	process_line(char *line, t_cmd **token_ptr)
{
	if (ft_strlen(line) <= 0)
		return (0);
	add_history(line);
	*token_ptr = tokenization(line);
	return (0);
}

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
		
		if(!line)
			exit(0);
		if (process_line(line, &var->list) != 0)
			continue ;
		if (syntax_error(line))
			free_cmd_list(var->list);
		else if (var->list)
		{
			expand_cmd_list(var->list, var);
			execute_commands(var);
			free_cmd_list(var->list);
		}
		else
			free(line);
	}
}

