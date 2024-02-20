/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:18:47 by lferro            #+#    #+#             */
/*   Updated: 2024/01/23 18:11:30 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcounter(char const *s, char c)
{
	int	i;
	int	index;
	int	count;

	i = 0;
	index = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && index == 0)
		{
			count++;
			index = 1;
		}
		else if (s[i] == c && index == 1)
			index = 0;
		i++;
	}
	return (count);
}

static char	*wordmaker(char const *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (word == 0)
		return (0);
	while (start < end)
		word[i++] = s[start++];
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = 0;
	j = 0;
	index = -1;
	res = malloc((wordcounter(s, c) + 1) * sizeof(char *));
	if (res == 0)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			res[j++] = wordmaker(s, index, i);
			index = -1;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}

// int main(void)
// {              //  01233456789
// 	char	*s  = "  abc  def  abc";
// 	char	c = ' ';
// 	// int		start = 0;
// 	// int		end = 4;

// 	printf("word count: %zu\n", wordcounter(s, c));

// 	char **split = ft_split(s, c);
// 	// printf("%s\n", wordmaker(s, start, end));

// 	for (size_t i = 0; i < wordcounter(s, c); i++)
// 		printf("%s\n", split[i]);

// 	return (0);
// }
