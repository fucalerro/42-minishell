/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:27:04 by lferro            #+#    #+#             */
/*   Updated: 2024/01/14 14:11:36 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Returns a pointer to a new string which is a duplicate of the string s.
 *
 * @param s
 * @return char*
 */
char	*ft_strdup(const char *s)
{
	char	*ds;
	size_t	i;

	if (s == NULL)
		return (NULL);
	ds = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (ds == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ds[i] = s[i];
		i++;
	}
	ds[i] = 0;
	return (ds);
}
