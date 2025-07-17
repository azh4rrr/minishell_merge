/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:12:30 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/17 12:27:11 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			exp.var_len = get_var_len(str, exp.i);
			if (exp.var_len > 1)
			{
				exp.var_name = extract_var_name(str, exp.i, exp.var_len);
				exp.expanded = get_expanded_value(exp.var_name, shell);
				exp.j += ft_strlen(exp.expanded);
				free(exp.var_name);
				free(exp.expanded);
				exp.i += exp.var_len;
				continue ;
			}
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
		if (token[exp.i] == '\'' && !exp.in_double)
			exp.in_single = !exp.in_single;
		else if (token[exp.i] == '"' && !exp.in_single)
			exp.in_double = !exp.in_double;
		if (token[exp.i] == '$' && !exp.in_single)
		{
			exp.var_len = get_var_len(token, exp.i);
			if (exp.var_len > 1)
			{
				exp.var_name = extract_var_name(token, exp.i, exp.var_len);
				exp.expanded = get_expanded_value(exp.var_name, shell);
				ft_strlcpy(exp.result + exp.j, exp.expanded,
					ft_strlen(exp.expanded) + 1);
				exp.j += ft_strlen(exp.expanded);
				free(exp.var_name);
				free(exp.expanded);
				exp.i += exp.var_len;
				continue ;
			}
		}
		if (token[exp.i] == '$' && token[exp.i - 1] != '"' && token[exp.i
			- 1] != '\'' && !exp.in_single && !exp.in_double)
			exp.i++;
		exp.result[exp.j++] = token[exp.i++];
	}
	exp.result[exp.j] = '\0';
	return (exp.result);
}

void	expand_cmd_array(char **cmd, t_shell *shell)
{
	int i;
	char *expanded;

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
