/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/29 14:35:11 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	**tokenizer(char *string, int status, char **env)
{
	t_tokenized tok;
	t_tokens	**tokens;
	int			i;

	if (is_quotes_opened(string))
		return (0);
	tok.normalized = input_normalizer(string);
	tok.space_tok = sp_tokenizer(tok.normalized, ' ');
	expand_env_vars(tok.space_tok, status, env);
	tok.op_tok = palloc(count_arr_elems(tok.space_tok), sizeof(char **));
	i = -1;
	while (tok.space_tok[++i])
		tok.op_tok[i] = op_tokenizer(tok.space_tok[i]);
	tok.op_tok[i] = 0;
	tok.tok = flatten_3d_array(tok.op_tok);
	tokens = quotes_tokenizer(tok.tok);
	free(tok.normalized);
	free_2starchar(tok.space_tok);
	free_2starchar(tok.tok);
	return (tokens);
}

void	normalize_loop(char *input, int i, char **output)
{
	int	j;
	int	flag;

	j = 0;
	while (input[i])
	{
		while (is_in_quotes(input, i) > 0 && input[i])
			(*output)[j++] = input[i++];
		if (ft_isspace(input[i]) && ft_isspace(input[i]) != ' ')
			(*output)[j++] = ' ';
		else if (ft_isspace(input[i]))
		{
			if (flag && input[i + 1] != 0 && !ft_isspace(input[i + 1]))
				(*output)[j++] = ' ';
		}
		else
		{
			(*output)[j++] = input[i];
			flag = 1;
		}
		i++;
	}
	(*output)[j] = 0;
}

char	*input_normalizer(char *input)
{
	int		i;
	char	*output;

	// output = palloc(ft_strlen(input) + 1, sizeof(char));
	output = palloc(ft_strlen(input) + 1, sizeof(char));
	if (!output)
		return (0);
	i = 0;
	while (ft_isspace(input[i]) && input[i])
	{
		if (ft_isspace(input[i]) != 32)
			output[i] = ' ';
		i++;
	}
	normalize_loop(input, i, &output);
	return (output);
}
