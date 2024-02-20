/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:01:41 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:34 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_buf;

	s_buf = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s_buf[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
