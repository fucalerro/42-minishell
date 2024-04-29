/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_op(char *string, int i)
{
	char	*single_op;

	single_op = "&|<>()";
	if (string[i] && ft_strchr(single_op, string[i]))
		return (true);
	return (false);
}

int	is_double_op(char *string, int i)
{
	if (string[i] == 0 || string[i + 1] == 0)
		return (false);
	if (!ft_strncmp(&string[i], "<<", 2) || !ft_strncmp(&string[i], ">>", 2))
		return (true);
	return (false);
}

int	count_op(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if ((is_single_op(string, i) || is_double_op(string, i))
			&& !is_in_quotes(string, i))
			count++;
		i++;
	}
	return (count);
}

int	count_quotes(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (is_quote(string[i]))
			count++;
		i++;
	}
	return (count);
}

int	is_quotes_opened(char *string)
{
	int	len;

	len = ft_strlen(string);
	if (is_in_quotes(string, len - 1) || count_quotes(string) == 1)
	{
		write_err("Quotes are not closed\n");
		return (1);
	}
	return (0);
}
