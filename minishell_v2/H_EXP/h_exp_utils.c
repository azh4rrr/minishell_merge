/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:12:30 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 18:34:25 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calculate_variable_length(char *str, t_exp *exp, t_shell *shell)
{
	exp->var_len = get_var_len(str, exp->i);
	if (exp->var_len > 1)
	{
		exp->var_name = extract_var_name(str, exp->i, exp->var_len);
		exp->expanded = get_expanded_value(exp->var_name, shell);
		exp->j += ft_strlen(exp->expanded);
		free(exp->var_name);
		free(exp->expanded);
		exp->i += exp->var_len;
		return (1);
	}
	return (0);
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
			if (calculate_variable_length(str, &exp, shell))
				continue ;
		}
		exp.j++;
		exp.i++;
	}
	return (exp.j);
}

static int	process_variable_expansion(char *token, t_exp *exp, t_shell *shell)
{
	exp->var_len = get_var_len(token, exp->i);
	if (exp->var_len > 1)
	{
		exp->var_name = extract_var_name(token, exp->i, exp->var_len);
		exp->expanded = get_expanded_value(exp->var_name, shell);
		ft_strlcpy(exp->result + exp->j, exp->expanded, ft_strlen(exp->expanded)
			+ 1);
		exp->j += ft_strlen(exp->expanded);
		free(exp->var_name);
		free(exp->expanded);
		exp->i += exp->var_len;
		return (1);
	}
	return (0);
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
			if (process_variable_expansion(token, &exp, shell))
				continue ;
		}
		if (token[exp.i] == '$' && token[exp.i - 1] != '"' && token[exp.i
				- 1] != '\'' && !exp.in_single && !exp.in_double)
			exp.i++;
		exp.result[exp.j++] = token[exp.i++];
	}
	return (exp.result[exp.j] = '\0', exp.result);
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
