/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_line_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:25:30 by azhar             #+#    #+#             */
/*   Updated: 2025/07/20 00:30:04 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

static void	process_quotes(char c, t_exp *exp)
{
   if (c == '\'' && exp->in_double == 0)
   	exp->in_single = !exp->in_single;
   else if (c == '"' && exp->in_single == 0)
   	exp->in_double = !exp->in_double;
}

static char	*check_special_vars(char *token, int i)
{
   if (token[i + 1] == '\0')
   	return (ft_strdup("$"));
   if (token[i + 1] == '0')
   	return (ft_strdup("minishell"));
   return (NULL);
}

static void	insert_split_tokens(char **split_parts, t_exp *exp)
{
   int	k;

   k = 0;
   while (split_parts[k])
   {
   	ft_strlcpy(exp->result + exp->j, split_parts[k],
   		ft_strlen(split_parts[k]) + 1);
   	exp->j += ft_strlen(split_parts[k]);
   	if (split_parts[k + 1])
   		exp->result[exp->j++] = ' ';
   	k++;
   }
   free_cmd_array(split_parts);
}

static void	preserve_original_var(char *token, t_exp *exp, int var_len)
{
   int	var_start;

   var_start = exp->i;
   while (var_start < exp->i + var_len)
   {
   	exp->result[exp->j++] = token[var_start++];
   }
}

static void	process_variable(char *token, t_shell *shell, t_exp *exp)
{
   char	*var_name;
   char	*expanded;
   char	**split_parts;

   exp->var_len = get_var_len(token, exp->i);
   if (exp->var_len <= 1)
   	return ;
   var_name = extract_var_name(token, exp->i, exp->var_len);
   expanded = get_expanded_value(var_name, shell);
   if (expanded && ft_strchr(expanded, ' '))
   {
   	split_parts = ft_split(expanded, ' ');
   	if (split_parts)
   		insert_split_tokens(split_parts, exp);
   }
   else
   	preserve_original_var(token, exp, exp->var_len);
   free(var_name);
   free(expanded);
   exp->i += exp->var_len;
}

char	*expand_cmd(char *token, t_shell *shell)
{
   t_exp	exp;
   char	*special;

   init_expand(&exp);
   if (!token)
   	return (NULL);
   exp.result = malloc(calculate_expanded_length(token, shell) + 1);
   if (!exp.result)
   	return (NULL);
   while (token[exp.i])
   {
   	process_quotes(token[exp.i], &exp);
   	if (token[exp.i] == '$' && !exp.in_single)
   	{
   		special = check_special_vars(token, exp.i);
   		if (special)
   			return (special);
   		process_variable(token, shell, &exp);
   		continue ;
   	}
   	if (token[exp.i] == '$' && token[exp.i - 1] != '"'
   		&& token[exp.i - 1] != '\'' && !exp.in_single
   		&& !exp.in_double)
   		exp.i++;
   	exp.result[exp.j++] = token[exp.i++];
   }
   exp.result[exp.j] = '\0';
   return (exp.result);
}