/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:17:31 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*op_tokenzier_loop(char *string, int *i, int *op_flag, int *start)
{
	char	*token;

	if (is_double_op(string, *i) && !*op_flag && !is_in_quotes(string, *i))
	{
		*op_flag = true;
		token = ft_substr(string, *i, 2);
		*i += 2;
	}
	else if (is_single_op(string, *i) && !*op_flag && !is_in_quotes(string, *i))
	{
		*op_flag = true;
		token = ft_substr(string, (*i)++, 1);
	}
	else
	{
		*start = *i;
		while (string[*i] && ((!is_double_op(string, *i)
					&& !is_single_op(string, *i)) || is_in_quotes(string, *i)))
			(*i)++;
		token = ft_substr(string, *start, *i - *start);
		*op_flag = false;
	}
	return (token);
}

char	**op_tokenizer(char *string)
{
	char	**res;
	int		op_flag;
	int		i;
	int		j;
	int		start;

	res = palloc((count_op(string) + 1) * 2, sizeof(char *));
	i = 0;
	j = 0;
	op_flag = 0;
	while (string[i])
		res[j++] = op_tokenzier_loop(string, &i, &op_flag, &start);
	res[j] = 0;
	return (res);
}

char	**sp_tokenizer(char *string, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = -1;
	j = 0;
	index = -1;
	res = malloc((wordcounter(string, c) + 1) * sizeof(char *));
	if (res == 0)
		return (0);
	while (++i <= ft_strlen(string))
	{
		if (string[i] != c && index < 0)
			index = i;
		else if ((string[i] == c || i == ft_strlen(string)) && index >= 0
			&& !is_in_quotes(string, i))
		{
			res[j++] = wordmaker(string, index, i);
			index = -1;
		}
	}
	res[j] = 0;
	return (res);
}

char	*set_is_in_quotes(char *token)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!res)
		return (0);
	i = 0;
	while (token[i])
	{
		if (is_in_quotes(token, i) == SINGLE_QUOTE)
			res[i] = 'S';
		else if (is_in_quotes(token, i) == DOUBLE_QUOTE)
			res[i] = 'D';
		else
			res[i] = 'N';
		i++;
	}
	return (res);
}

t_tokens	**quotes_tokenizer(char **tokens)
{
	int			i;
	t_tokens	**res;
	char		*temp;

	res = malloc(sizeof(t_tokens *) * (count_arr_elems(tokens) + 1));
	if (!res)
		return (0);
	i = 0;
	while (tokens[i])
	{
		res[i] = malloc(sizeof(t_tokens));
		if (!res[i])
			return (0);
		res[i]->quote = is_quote(tokens[i][0]);
		temp = all_quotes_remover(tokens[i]);
		res[i]->tok = ft_strdup(temp);
		if (!res[i]->tok)
			return (NULL);
		free(temp);
		i++;
	}
	res[i] = 0;
	return (res);
}
