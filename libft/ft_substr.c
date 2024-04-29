/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:14:58 by lferro            #+#    #+#             */
/*   Updated: 2024/02/13 17:59:16 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a substring from the
 * string ’s’. of size len. The substring begins at index ’start’.
 *
 * @param s string to substring
 * @param start start index of the substring
 * @param len len of the substring
 * @return char*
 */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	start = (size_t)start;
	i = 0;
	j = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	res = palloc(len + 1, sizeof(char));
	if (res == 0)
		return (0);
	while (i < start && *s)
		i++;
	while (i >= start && i < len + start)
		res[j++] = s[i++];
	res[j] = 0;
	return (res);
}

// int main(int argc, char const *argv[])
// {

// 	// char s1[] = "lorem ipsum dolor sit amet";
// 	// int start = 400;
// 	// int len = 20;

// 	printf("ft: %s\n", ft_substr("tripouille", 0, 42000));

// 	return (0);
// }
