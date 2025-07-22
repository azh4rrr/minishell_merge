/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:03:36 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 23:26:41 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_variable_expansion(char *str, int i, t_shell *shell, int *new_i)
{
	int		var_len;
	char	*var_name;
	char	*expanded;
	int		len;

	len = 0;
	var_len = get_var_len(str, i);
	if (var_len > 1)
	{
		var_name = extract_var_name(str, i, var_len);
		expanded = get_expanded_value(var_name, shell);
		len = ft_strlen(expanded);
		free(var_name);
		free(expanded);
		*new_i = i + var_len;
	}
	else
	{
		len = 1;
		*new_i = i + 1;
	}
	return (len);
}

int	calculate_expanded_length(char *str, t_shell *shell)
{
	t_exp	exp;

	init_expand(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' && !exp.in_double)
			exp.in_single = !exp.in_single;
		else if (str[exp.i] == '"' && !exp.in_single)
			exp.in_double = !exp.in_double;
		if (str[exp.i] == '$' && !exp.in_single)
		{
			exp.j += process_variable_expansion(str, exp.i, shell, &exp.i);
			continue ;
		}
		exp.j++;
		exp.i++;
	}
	return (exp.j);
}

char	*expand_variables_in_token(char *token, t_shell *shell)
{
	t_exp	exp;

	init_expand(&exp);
	if (!token)
		return (NULL);
	exp.result = malloc(calculate_expanded_length(token, shell) + 1);
	if (!exp.result)
		return (NULL);
	while (token[exp.i])
	{
		h_quotes(token[exp.i], &exp);
		if (token[exp.i] == '$')
			process_dollar_sign(token, &exp, shell);
		else
			exp.result[exp.j++] = token[exp.i++];
	}
	exp.result[exp.j] = '\0';
	return (exp.result);
}

void	expand_cmd_array(char **cmd, t_shell *shell)
{
	int		i;
	char	*expanded;

	if (!cmd || !shell)
		return ;
	i = 0;
	while (cmd[i])
	{
		expanded = expand_variables_in_token(cmd[i], shell);
		if (expanded)
		{
			free(cmd[i]);
			cmd[i] = expanded;
		}
		i++;
	}
}

void	expand_redirection_list(t_redirec *redirec, t_shell *shell)
{
	t_redirec	*current;
	char		*expanded;

	if (!redirec || !shell)
		return ;
	current = redirec;
	while (current)
	{
		expanded = expand_variables_in_token(current->name, shell);
		if (expanded && current->type != D_HERDOC
			&& current->type != D_HERDOC_Q)
		{
			free(current->name);
			current->name = expanded;
		}
		else if (expanded)
			free(expanded);
		current = current->next;
	}
}
