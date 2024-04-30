/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 16:31:20 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_2starchar(char **strstr)
{
	int	i;

	i = 0;
	if (!strstr || !*strstr)
		return (NULL);

	while (strstr[i])
		free(strstr[i++]);
	free(strstr);
	strstr = NULL;
	return (NULL);
}

void	free_tokens(t_tokens **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->tok)
			free(tokens[i]->tok);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
