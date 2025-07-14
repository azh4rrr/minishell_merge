/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:54:21 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/05 13:49:37 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
