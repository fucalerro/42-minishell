/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:52:13 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:57:47 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_buf;
	const unsigned char	*src_buf;

	if (dest == 0 && src == 0)
		return (0);
	dest_buf = (unsigned char *)dest;
	src_buf = (unsigned char *)src;
	while (n--)
		*dest_buf++ = *src_buf++;
	return (dest);
}
