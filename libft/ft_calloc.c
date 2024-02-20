/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:19 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:12 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*res;

	if (nelem == 0 || elsize == 0)
	{
		res = malloc(0);
		if (res == 0)
			return (0);
		return (res);
	}
	res = malloc(elsize * nelem);
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, elsize * nelem);
	return (res);
}
