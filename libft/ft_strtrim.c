/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:32:01 by lferro            #+#    #+#             */
/*   Updated: 2024/02/13 17:59:30 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief
 *
 * @param s1
 * @param set
 * @return char*
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

// int main(void)
// {
// 	const char *str = "   $$  asd  $$ ";
// 	const char *set = " $";
// 	char *newstr = ft_strtrim(str, set);
// 	printf("%s", newstr);
// 	// printf("");
// 	return (0);
// }
