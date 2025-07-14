/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:06:02 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/28 13:10:13 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ma;
	size_t	mlen;
	size_t	b;

	if (!s)
		return (NULL);
	mlen = ft_strlen(s);
	b = 0;
	if (start >= (unsigned int)mlen)
		return (ft_strdup(""));
	if (len > mlen - start)
		len = mlen - start;
	ma = (char *)malloc(sizeof(char) * (len + 1));
	if (!ma)
		return (strerror(errno), NULL);
	while (b < len)
	{
		ma[b] = s[start + b];
		b++;
	}
	ma[b] = '\0';
	return (ma);
}
