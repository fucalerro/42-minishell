/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:09:35 by lferro            #+#    #+#             */
/*   Updated: 2023/11/27 14:29:41 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	count = 2;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*max_int_or_zero_mngmt(int n)
{
	char	*str;

	if (n == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (str == 0)
			return (0);
		str[0] = '0';
		str[1] = 0;
	}
	else
		str = ft_strdup("-2147483648");
	return (str);
}

static char	*mallocator(int count)
{
	char	*anbr;

	anbr = malloc(sizeof(char) * count);
	if (anbr == 0)
		return (0);
	return (anbr);
}

char	*ft_itoa(int n)
{
	char	*anbr;
	size_t	*i;

	i = (size_t[]){0, n, 0};
	if (n == 0 || n == -2147483648)
	{
		anbr = max_int_or_zero_mngmt(n);
		return (anbr);
	}
	i[0] = count_digit(n);
	anbr = mallocator(i[0]);
	if (anbr == 0)
		return (0);
	if (n < 0)
		anbr[0] = '-';
	if (n < 0)
		n = -n;
	anbr[--i[0]] = 0;
	while (n > 0)
	{
		anbr[i[0]-- - 1] = (n % 10) + 48;
		n /= 10;
	}
	return (anbr);
}
