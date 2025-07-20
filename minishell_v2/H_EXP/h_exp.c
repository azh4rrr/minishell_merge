/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:38:51 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 18:38:55 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_dollar_quote(char *token, t_exp *exp)
{
	exp->result[exp->j++] = token[exp->i++];
	exp->result[exp->j++] = token[exp->i++];
	return (1);
}

// Handles quote tracking and variable expansion for a single character
static int	process_quotes_and_vars(char *token, t_exp *exp, t_shell *shell)
{
	if (token[exp->i] == '$')
	{
		if (token[exp->i + 1] == '"' || token[exp->i + 1] == '\'')
			return (handle_dollar_quote(token, exp));
		if (ft_strlen(token) == 2)
			return (2);
		if (token[exp->i + 1] == '0')
			return (3);
		exp->var_len = get_var_len(token, exp->i);
		if (exp->var_len > 1)
		{
			exp->var_name = extract_var_name(token, exp->i, exp->var_len);
			exp->expanded = get_expanded_value(exp->var_name, shell);
			ft_strlcpy(exp->result + exp->j, exp->expanded,
				ft_strlen(exp->expanded) + 1);
			exp->j += ft_strlen(exp->expanded);
			free(exp->var_name);
			free(exp->expanded);
			exp->i += exp->var_len;
			return (1);
		}
	}
	return (0);
}

static int	process_regular_chars(char *token, t_exp *exp)
{
	if (token[exp->i] == '$' && token[exp->i - 1] != '"' && token[exp->i
			- 1] != '\'' && !exp->in_single && !exp->in_double)
	{
		exp->i++;
		return (0);
	}
	exp->result[exp->j++] = token[exp->i++];
	return (0);
}

// Main expansion function
char	*expand_variables_in_heredoc(char *token, t_shell *shell)
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
		exp.res = process_quotes_and_vars(token, &exp, shell);
		if (exp.res == -1)
			return (free(exp.result), ft_strdup(token));
		if (exp.res == 2)
			return (free(exp.result), ft_strdup("$\n"));
		if (exp.res == 3)
			return (free(exp.result), ft_strdup("minishell\n"));
		if (exp.res > 0)
			continue ;
		exp.res = process_regular_chars(token, &exp);
		if (exp.res == -1)
			return (free(exp.result), ft_strdup(token));
	}
	exp.result[exp.j] = '\0';
	return (exp.result);
}

void	expand_cmd_heredoc(char **cmd, t_shell *shell, int fd)
{
	char	*expanded;

	if (!cmd || !shell)
		return ;
	if (cmd[0])
	{
		expanded = expand_variables_in_heredoc(cmd[0], shell);
		if (expanded)
		{
			ft_putstr_fd(expanded, fd);
			free(expanded);
		}
	}
}
