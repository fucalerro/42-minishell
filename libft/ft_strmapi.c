/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:44:41 by lferro            #+#    #+#             */
/*   Updated: 2023/10/12 11:45:29 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = f((int)i, (char)s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

// char	func( unsigned int n, char c)
// {
// 	if ((c >= 'a' && c <= 'z') && (n % 2 == 0))
// 		c = c - 32;
// 	return (c);
// }

// int main()
// {
// 	char *s = "je mange du pain";
// 	char *newstr = ft_strmapi(s, func);
// 	printf("%s", newstr);
// 	return (0);
// }
