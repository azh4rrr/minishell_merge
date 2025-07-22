/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:19:26 by azhar             #+#    #+#             */
/*   Updated: 2025/07/20 22:08:40 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_char(char c)
{
	return (c == '_' || c == '?' || c == '*' || c == '@' || ft_isalnum(c));
}

int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

void	init_split(t_split *split, char *str, char delimiter)
{
	split->str = str;
	split->delimiter = delimiter;
	split->i = 0;
	split->start = 0;
	split->token_idx = 0;
	split->token_count = 0;
	split->in_single = 0;
	split->in_double = 0;
	split->tokens = NULL;
}

void	init_expand(t_exp *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->in_single = 0;
	exp->in_double = 0;
	exp->var_len = 0;
	exp->expanded = NULL;
	exp->var_name = NULL;
	exp->result = NULL;
}
