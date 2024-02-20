/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:47:52 by lferro            #+#    #+#             */
/*   Updated: 2023/10/29 19:56:54 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*chardest;
	unsigned const char	*charsrc;
	size_t				i;

	chardest = (unsigned char *)dest;
	charsrc = (unsigned const char *)src;
	i = 0;
	if (chardest == charsrc)
		return (dest);
	if (charsrc < chardest)
		while (++i <= n)
			chardest[n - i] = charsrc[n - i];
	else
		while (n--)
			*chardest++ = *charsrc++;
	return (dest);
}
