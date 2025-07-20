/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:10:11 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/20 21:49:17 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_var_value(t_p_exp *ctx, char *value)
{
	size_t	vlen;

	vlen = ft_strlen(value);
	ft_strcpy(ctx->result + ctx->j, value);
	ctx->j += vlen;
	ctx->changed = 1;
}

static void	copy_var_name(const char *line, int i, t_p_exp *ctx, int var_len)
{
	ctx->result[ctx->j++] = '$';
	ft_strncpy(ctx->result + ctx->j, line + i + 1, var_len);
	ctx->j += var_len;
}

static int	handle_var_expansion(const char *line, int i, t_shell *shell,
		t_p_exp *ctx)
{
	int		var_len;
	char	*var_name;
	char	*value;

	var_len = 0;
	while (is_var_char(line[i + 1 + var_len]))
		var_len++;
	var_name = ft_substr(line, i + 1, var_len);
	if (!var_name)
		return (i + 1 + var_len);
	value = get_expanded_value(var_name, shell);
	if (value && ft_strchr(value, ' '))
		copy_var_value(ctx, value);
	else
		copy_var_name(line, i, ctx, var_len);
	free(var_name);
	if (value)
		free(value);
	return (i + 1 + var_len);
}

static void	process_char(const char *line, t_shell *shell, t_p_exp *ctx)
{
	if (line[ctx->i] == '$' && is_var_char(line[ctx->i + 1]))
		ctx->i = handle_var_expansion(line, ctx->i, shell, ctx);
	else
	{
		ctx->result[ctx->j++] = line[ctx->i];
		ctx->i++;
	}
}

char	*pre_expand_line_if_needed(char *line, t_shell *shell)
{
	t_p_exp	ctx;

	ctx = (t_p_exp){0, 0, 0, ft_strlen(line), NULL};
	ctx.result = malloc(ctx.len * 4 + 1);
	if (!ctx.result)
		return (NULL);
	while (line[ctx.i])
		process_char(line, shell, &ctx);
	ctx.result[ctx.j] = '\0';
	if (ctx.changed)
		return (ctx.result);
	free(ctx.result);
	return (ft_strdup(line));
}
