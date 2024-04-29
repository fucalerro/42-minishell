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
	char		*normalized_input;
	char		**sp_tokenized;
	char		***op_tokenized;
	int			i;
	t_tokens	**tokens;
	char		**tokenized;

	if (is_quotes_opened(string))
		return (0);
	normalized_input = input_normalizer(string);
	sp_tokenized = sp_tokenizer(normalized_input, ' ');
	expand_env_vars(sp_tokenized, status, env);
	op_tokenized = palloc(count_arr_elems(sp_tokenized), sizeof(char **));
	i = -1;
	while (sp_tokenized[++i])
		op_tokenized[i] = op_tokenizer(sp_tokenized[i]);
	op_tokenized[i] = 0;
	tokenized = flatten_3d_array(op_tokenized);
	tokens = quotes_tokenizer(tokenized);
	free(normalized_input);
	free_2starchar(sp_tokenized);
	free_2starchar(tokenized);
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

	output = malloc(sizeof(char) * (ft_strlen(input) + 1));
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
