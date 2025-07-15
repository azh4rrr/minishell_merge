
#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
char	*ft_strchr(const char *s, int c)
{
	size_t	x;

	x = 0;
	while (s[x])
	{
		if (s[x] == (char)c)
			return ((char *)s + x);
		x++;
	}
	if (s[x] == (char)c)
		return ((char *)s + x);
	return (NULL);
}

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

int	quoted(char *s)
{
	if (ft_strchr(s, '\''))
		return (1);
	if (ft_strchr(s, '"'))
		return (2);
	return (0);
}
char	*add_quotes(char *s)
{
	char	*d;

	d = malloc((ft_strlen(s) * 3) + 1);
	if (!s || quoted(s) == 0)
		return (NULL);
	if (quoted(s) == 1)
	{
		d[0] = '"';
		ft_strncpy(&d[1], s, ft_strlen(s));
		d[ft_strlen(s)] = '"';
	}
	else if (quoted(s) == 2)
	{
		d[0] = '\'';
		ft_strncpy(&d[1], s, ft_strlen(s));
		d[ft_strlen(s)] = '\'';
	}
	d[ft_strlen(s) + 2] = '\0';
	return (d);
}
#include <stdio.h>

int	main(void)
{
	char *line = malloc(100);
	line = add_quotes("testing \"");
	printf("%s", line);
}