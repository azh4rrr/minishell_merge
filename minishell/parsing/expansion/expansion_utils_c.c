/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:20:51 by azhar             #+#    #+#             */
/*   Updated: 2025/07/20 23:33:06 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	h_quotes(char c, t_exp *exp)
{
	if (c == '\'' && exp->in_double == 0)
		exp->in_single = !exp->in_single;
	else if (c == '"' && exp->in_single == 0)
		exp->in_double = !exp->in_double;
}

static int	handle_special_variables(char *token, t_exp *exp)
{
	char	*exit_status_str;

	if (token[exp->i + 1] == '\0')
		return (exp->result[exp->j++] = '$', exp->i++, 1);
	if (token[exp->i + 1] == '0')
	{
		free(exp->result);
		exp->result = ft_strdup("minishell");
		exp->j += 9;
		exp->i += 2;
		return (1);
	}
	if (token[exp->i + 1] == '?')
	{
		exit_status_str = ft_itoa(exit_status);
		if (!exit_status_str)
			return (exp->result[exp->j++] = '0', exp->i += 2, 1);
		ft_strlcpy(exp->result + exp->j, exit_status_str,
			ft_strlen(exit_status_str) + 1);
		exp->j += ft_strlen(exit_status_str);
		free(exit_status_str);
		exp->i += 2;
		return (1);
	}
	return (0);
}

static int	handle_variable_expansion(char *token, t_exp *exp, t_shell *shell)
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

void	process_dollar_sign(char *token, t_exp *exp, t_shell *shell)
{
	if (exp->in_single)
	{
		exp->result[exp->j++] = token[exp->i++];
		return ;
	}
	if (handle_special_variables(token, exp))
		return ;
	if (handle_variable_expansion(token, exp, shell))
		return ;
	if (token[exp->i + 1] == '"' || token[exp->i + 1] == '\'')
	{
		exp->i++;
		return ;
	}
	if (token[exp->i] == '$' && exp->i > 0 && token[exp->i - 1] != '"'
		&& token[exp->i - 1] != '\'' && !exp->in_single && !exp->in_double)
	{
		exp->i++;
		return ;
	}
	exp->result[exp->j++] = token[exp->i++];
}

void	p2char(char ***ptr)
{
	int	r;

	if (!ptr || !*ptr)
		return ;
	r = 0;
	while ((*ptr)[r])
		free((*ptr)[r++]);
	free(*ptr);
	*ptr = NULL;
}
