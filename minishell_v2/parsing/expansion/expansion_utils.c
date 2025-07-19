/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:03:36 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 00:50:02 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// Handle quote state changes
static void h_quotes(char c, t_exp *exp)
{
    if (c == '\'' && exp->in_double == 0)
        exp->in_single = !exp->in_single;
    else if (c == '"' && exp->in_single == 0)
        exp->in_double = !exp->in_double;
}

// Handle special variables like $0, $?
static int handle_special_variables(char *token, t_exp *exp)
{
    if (token[exp->i + 1] == '\0')
    {
        exp->result[exp->j++] = '$';
        exp->i++;
        return (1);
    }
    
    if (token[exp->i + 1] == '0')
    {
        ft_strlcpy(exp->result + exp->j, "minishell", 10);
        exp->j += 9;
        exp->i += 2;
        return (1);
    }
    
    if (token[exp->i + 1] == '?')
    {
        char *exit_status_str = ft_itoa(exit_status);
        if (!exit_status_str)
        {
            exp->result[exp->j++] = '0';
            exp->i += 2;
            return (1);
        }
        ft_strlcpy(exp->result + exp->j, exit_status_str, 
                   ft_strlen(exit_status_str) + 1);
        exp->j += ft_strlen(exit_status_str);
        free(exit_status_str);
        exp->i += 2;
        return (1);
    }
    
    return (0); // Not a special variable
}

// Handle regular variable expansion
static int handle_variable_expansion(char *token, t_exp *exp, t_shell *shell)
{
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
    return (0); // Variable length <= 1, not expanded
}

// Process dollar sign and variable expansion
static void process_dollar_sign(char *token, t_exp *exp, t_shell *shell)
{
    if (exp->in_single)
    {
        exp->result[exp->j++] = token[exp->i++];
        return;
    }
    
    // Handle special variables first
    if (handle_special_variables(token, exp))
        return;
    
    // Handle regular variable expansion
    if (handle_variable_expansion(token, exp, shell))
        return;
    
    // If we reach here, it's a standalone $ or invalid variable
    // Skip standalone $ if not quoted
    if (token[exp->i] == '$' && exp->i > 0 && 
        token[exp->i - 1] != '"' && token[exp->i - 1] != '\'' && 
        !exp->in_single && !exp->in_double)
    {
        exp->i++;
        return;
    }
    
    // Copy the character normally
    exp->result[exp->j++] = token[exp->i++];
}

// Main expansion function
char *expand_variables_in_token(char *token, t_shell *shell)
{
    t_exp exp;
    
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
		if (expanded && current->type != D_HERDOC && current->type != D_HERDOC_Q)
		{
			free(current->name);
			current->name = expanded;
		}
		current = current->next;
	}
}

void	p2char(char ***ptr)
{
	int r;

	if (!ptr || !*ptr)
		return ;
	r = 0;
	while ((*ptr)[r])
		free((*ptr)[r++]);
	free(*ptr);
	*ptr = NULL;
}