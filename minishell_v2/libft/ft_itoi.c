/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:12:00 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 00:12:02 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strleen(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		j;
	char	*p;

	j = 0;
	len = strleen(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		j = 1;
		n = -n;
	}
	while (len-- > j)
	{
		p[len] = (n % 10) + 48;
		n /= 10;
	}
	return (p);
}
