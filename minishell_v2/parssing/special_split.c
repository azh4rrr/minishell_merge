#include "../minishell.h"

void	update_quotes_and_skip(char *str, int *i, int *in_single,
		int *in_double, char delimiter)
{
	while (str[*i])
	{
		if (str[*i] == '\'' && !(*in_double))
			*in_single = !(*in_single);
		else if (str[*i] == '"' && !(*in_single))
			*in_double = !(*in_double);
		if (str[*i] == delimiter && !(*in_single) && !(*in_double))
			break ;
		(*i)++;
	}
}

int	count_and_skip_delimiters(char *str, int *i, char delimiter)
{
	int	in_single;
	int	in_double;
	int	token_count;

	token_count = 0;
	in_single = 0;
	in_double = 0;
	while (str[*i])
	{
		while (str[*i] == delimiter && !in_single && !in_double)
			(*i)++;
		if (!str[*i])
			break ;
		token_count++;
		update_quotes_and_skip(str, i, &in_single, &in_double, delimiter);
	}
	return (token_count);
}

char	*extract_single_token(char *str, int start, int end)
{
	char	*token;
	int		i;

	token = malloc(end - start + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (start < end)
	{
		token[i] = str[start];
		i++;
		start++;
	}
	token[i] = '\0';
	return (token);
}

void	cleanup_tokens(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

char	**allocate_and_extract(char *str, char delimiter, int token_count)
{
	char	**tokens;
	int		i;
	int		token_idx;
	int		start;
	int		in_single;
	int		in_double;

	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	token_idx = 0;
	in_single = 0;
	in_double = 0;
	while (str[i] && token_idx < token_count)
	{
		while (str[i] == delimiter && !in_single && !in_double)
			i++;
		if (!str[i])
			break ;
		start = i;
		update_quotes_and_skip(str, &i, &in_single, &in_double, delimiter);
		tokens[token_idx] = extract_single_token(str, start, i);
		if (!tokens[token_idx])
			return (cleanup_tokens(tokens, token_idx), NULL);
		token_idx++;
	}
	tokens[token_idx] = NULL;
	return (tokens);
}

char	**quote_aware_split(char *str, char delimiter)
{
	int token_count;
	int i;
	char **empty_result;

	if (!str)
		return (NULL);
	i = 0;
	token_count = count_and_skip_delimiters(str, &i, delimiter);
	if (token_count == 0)
	{
		empty_result = malloc(sizeof(char *));
		if (empty_result)
			empty_result[0] = NULL;
		return (empty_result);
	}
	return (allocate_and_extract(str, delimiter, token_count));
}